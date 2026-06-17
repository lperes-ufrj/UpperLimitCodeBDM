#!/usr/bin/env python3
"""Plot BDT input variables after applying a BDT response cut.

Edit the configuration block below to change the XML file, score cut, input
ROOT file, or output file. There is intentionally no argparse interface.
"""

from __future__ import annotations

import os
import subprocess
import tempfile
import time
import warnings
import xml.etree.ElementTree as ET
from pathlib import Path

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib-cache")
warnings.filterwarnings("ignore", message="Unable to import Axes3D.*")

import matplotlib
import numpy as np
import uproot

matplotlib.use("Agg")
import matplotlib.pyplot as plt

try:
    import dunestyle.matplotlib as dunestyle
except (AssertionError, ImportError):
    dunestyle = None


# -----------------------------
# Configuration
# -----------------------------
SCRIPT_DIR = Path(__file__).resolve().parent

INPUT_ROOT_FILE = Path(
    "~/ntuples_grid_newVertex/00a_newVertex/"
    "atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M_1M.root"
).expanduser()
TREE_NAME = "ana/Atm"

BDM_SAMPLE_DIR = Path("~/ntuples_grid_newVertex/00a_newVertex").expanduser()
BDM_SAMPLE_FILES = {
    r"BDM $m_\chi=10$ GeV, $\gamma=1.1$": "bdm_m10_b1p1_00a.root",
    # Add more samples here, for example:
    # r"BDM $m_\chi=20$ GeV, $\gamma=1.1$": "bdm_m20_b1p1_00a.root",
}

BDT_XML_FILE = (
    SCRIPT_DIR
    / "dataset_202605112035/weights/"
    "TMVAClassification_202605112035_BDTAtmCCNC_202605112035.weights.xml"
)

BDT_SCORE_CUT = 0.3
OUTPUT_PDF = SCRIPT_DIR / f"bdt_selected_inputs_score_gt_{BDT_SCORE_CUT:g}_{time.strftime('%Y%m%d')}.pdf"

CLASS_BRANCH = "CCNC"
NC_VALUE = 1
N_BINS = 40
MAX_EVENTS = None  # Set to an integer for a quick test.


def parse_bdt_variables(xml_file: Path) -> list[str]:
    xml_file = xml_file.expanduser().resolve()
    if not xml_file.exists():
        raise FileNotFoundError(f"TMVA weights XML not found: {xml_file}")

    root = ET.parse(xml_file).getroot()
    expressions = None
    for variables in root.iter("Variables"):
        expressions = [
            item.attrib["Expression"]
            for item in variables
            if "Expression" in item.attrib
        ]
        break
    if not expressions:
        raise RuntimeError(f"No <Variables> block found in {xml_file}")

    return expressions


def cpp_string(value: Path | str) -> str:
    return str(value).replace("\\", "\\\\").replace('"', '\\"')


def resolve_sample_path(path: str | Path, base_dir: Path | None = None) -> Path:
    path = Path(path).expanduser()
    if not path.is_absolute() and base_dir is not None:
        path = base_dir / path
    return path.resolve()


def branch_for_variable(variable: str) -> str:
    if variable.startswith("log(") and variable.endswith(")"):
        return variable[4:-1].strip()
    return variable


def scalar_array(values: np.ndarray) -> np.ndarray:
    values = np.asarray(values)
    if values.dtype != object:
        return values.reshape(-1)

    out = np.empty(len(values), dtype=np.float64)
    for idx, item in enumerate(values):
        item = np.asarray(item).reshape(-1)
        out[idx] = item[0] if item.size else np.nan
    return out


def values_for_variable(arrays: dict[str, np.ndarray], variable: str) -> np.ndarray:
    branch = branch_for_variable(variable)
    values = scalar_array(arrays[branch])
    if variable.startswith("log(") and variable.endswith(")"):
        values = np.log(np.clip(values.astype(np.float64), 1.0e-6, None))
    return values.astype(np.float64)


def load_root_arrays(
    root_file: Path,
    tree_name: str,
    branches: list[str],
    max_events: int | None,
) -> dict[str, np.ndarray]:
    root_file = root_file.expanduser().resolve()
    if not root_file.exists():
        raise FileNotFoundError(f"Input ROOT file not found: {root_file}")

    with uproot.open(root_file) as handle:
        if tree_name not in handle:
            available = ", ".join(handle.keys())
            raise KeyError(f"Tree '{tree_name}' not found in {root_file}. Keys: {available}")

        tree = handle[tree_name]
        branches = list(dict.fromkeys(branches))
        missing = [branch for branch in branches if branch not in tree.keys()]
        if missing:
            raise KeyError(f"Missing branch(es) in {tree_name}: {', '.join(missing)}")

        return tree.arrays(branches, library="np", entry_stop=max_events)


def evaluate_bdt_response(
    root_file: Path,
    tree_name: str,
    xml_file: Path,
    variables: list[str],
    max_events: int | None,
) -> np.ndarray:
    """Evaluate BDT scores with ROOT's C++ interpreter and return one score per event."""
    root_file = Path(root_file).expanduser().resolve()
    xml_file = Path(xml_file).expanduser().resolve()

    variable_declarations = "\n".join(
        f'  Float_t var_{idx} = 0.0; reader.AddVariable("{cpp_string(variable)}", &var_{idx});'
        for idx, variable in enumerate(variables)
    )
    formula_declarations = "\n".join(
        f'  TTreeFormula formula_{idx}("formula_{idx}", "{cpp_string(variable)}", tree);'
        for idx, variable in enumerate(variables)
    )
    formula_sync = "\n".join(
        f"    formula_{idx}.GetNdata();" for idx in range(len(variables))
    )
    assignments = "\n".join(
        f"    var_{idx} = static_cast<Float_t>(formula_{idx}.EvalInstance());"
        for idx in range(len(variables))
    )

    with tempfile.TemporaryDirectory(prefix="bdt_selected_scores_") as tmpdir:
        tmpdir = Path(tmpdir)
        macro_file = tmpdir / "evaluate_selected_scores.C"
        scores_file = tmpdir / "scores.txt"

        macro_file.write_text(
            f"""
#include <TMVA/Reader.h>
#include <TMVA/Tools.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>
#include <TTreeFormula.h>
#include <fstream>
#include <iostream>

void evaluate_selected_scores() {{
  TMVA::Tools::Instance();

  TFile* file = TFile::Open("{cpp_string(root_file)}");
  if (!file || file->IsZombie()) {{
    std::cerr << "Could not open ROOT file: {cpp_string(root_file)}" << std::endl;
    gSystem->Exit(10);
  }}

  TTree* tree = static_cast<TTree*>(file->Get("{cpp_string(tree_name)}"));
  if (!tree) {{
    std::cerr << "Could not find tree: {cpp_string(tree_name)}" << std::endl;
    gSystem->Exit(11);
  }}

  TMVA::Reader reader("!Color:!Silent");
{variable_declarations}
  reader.BookMVA("TMVAClassification", "{cpp_string(xml_file)}");
{formula_declarations}

  Long64_t nentries = tree->GetEntries();
  const Long64_t max_events = {max_events if max_events is not None else -1};
  if (max_events > 0 && max_events < nentries) nentries = max_events;

  std::ofstream out("{cpp_string(scores_file)}");
  for (Long64_t entry = 0; entry < nentries; ++entry) {{
    tree->GetEntry(entry);
{formula_sync}
{assignments}
    out << reader.EvaluateMVA("TMVAClassification") << "\\n";
  }}

  out.close();
  file->Close();
}}
""".lstrip()
        )

        result = subprocess.run(
            ["root", "-l", "-b", "-q", str(macro_file)],
            text=True,
            capture_output=True,
            check=False,
        )
        if result.returncode != 0:
            raise RuntimeError(
                "ROOT BDT score evaluation failed.\n"
                f"stdout:\n{result.stdout}\n"
                f"stderr:\n{result.stderr}"
            )

        if not scores_file.exists() or scores_file.stat().st_size == 0:
            return np.array([], dtype=np.float64)
        return np.atleast_1d(np.loadtxt(scores_file, dtype=np.float64))


def histogram_bins(values: np.ndarray, variable: str) -> np.ndarray:
    values = values[np.isfinite(values)]
    if values.size == 0:
        return np.linspace(0.0, 1.0, N_BINS + 1)

    if variable == "LongestTrack":
        return np.linspace(0.0, 400.0, N_BINS + 1)

    if variable == "LongestShower":
        return np.linspace(0.0, 300.0, N_BINS + 1)

    if variable == "NHits" and np.nanmin(values) > 0:
        low = float(np.nanmin(values))
        high = float(np.nanmax(values))
        if np.isclose(low, high):
            low *= 0.9
            high *= 1.1
        return np.geomspace(low, high, N_BINS + 1)

    if variable in {"nTracks", "nShowers"}:
        low = np.floor(np.nanmin(values)) - 0.5
        high = np.ceil(np.nanmax(values)) + 0.5
        return np.arange(low, high + 1.0, 1.0)

    low = float(np.nanmin(values))
    high = float(np.nanmax(values))
    if np.isclose(low, high):
        low -= 0.5
        high += 0.5
    return np.linspace(low, high, N_BINS + 1)


def plot_selected_variables(
    arrays: dict[str, np.ndarray],
    variables: list[str],
    nc_selected_mask: np.ndarray,
    nc_full_mask: np.ndarray,
    bdm_samples: dict[str, tuple[dict[str, np.ndarray], np.ndarray]],
    output_pdf: Path,
) -> None:
    nvars = len(variables)
    ncols = 2
    nrows = int(np.ceil(nvars / ncols))

    fig, axes = plt.subplots(nrows, ncols, figsize=(10, 3 * nrows), dpi=150)
    axes = np.atleast_1d(axes).flatten()
    legend_handles = []
    legend_labels = []

    for idx, variable in enumerate(variables):
        ax = axes[idx]
        values = values_for_variable(arrays, variable)
        nc_full_values = values[nc_full_mask]
        nc_selected_values = values[nc_selected_mask]
        bdm_values_by_label = {}
        combined_values = [nc_full_values, nc_selected_values]
        for label, (sample_arrays, selected_mask) in bdm_samples.items():
            sample_values = values_for_variable(sample_arrays, variable)[selected_mask]
            bdm_values_by_label[label] = sample_values
            combined_values.append(sample_values)

        bins = histogram_bins(np.concatenate(combined_values), variable)

        if nc_full_values.size:
            ax.hist(
                nc_full_values,
                bins=bins,
                density=True,
                label=rf"Atm. $\nu$ NC (all)",
                histtype="step"
            )
        colors = plt.cm.viridis(np.linspace(0.5, 0.9, max(len(bdm_values_by_label), 1)))
        for color, (label, sample_values) in zip(colors, bdm_values_by_label.items()):
            if not sample_values.size:
                continue
            ax.hist(
                sample_values,
                bins=bins,
                density=True,
                label=label,
                color=color,
                histtype="step",
                linewidth=3.
            )
        if nc_selected_values.size:
            ax.hist(
                nc_selected_values,
                bins=bins,
                density=True,
                label=rf"Atm. $\nu$ NC (BDT > {BDT_SCORE_CUT:g})",
                histtype="step"
            )



        ax.set_xlabel(variable)
        ax.set_ylabel("Normalized Entries")
        if variable == "NHits" and np.all(bins > 0):
            ax.set_xscale("log")
        if dunestyle is not None:
            dunestyle.Simulation(0.4, 0.5, ax=ax)
        ax.grid(True)

        if not legend_handles:
            legend_handles, legend_labels = ax.get_legend_handles_labels()

    for idx in range(nvars, len(axes)):
        fig.delaxes(axes[idx])

    fig.suptitle(
        f"All NC vs NC and BDM events with BDT score > {BDT_SCORE_CUT:g}",
        y=0.995,
    )
    if legend_handles:
        fig.legend(
            legend_handles,
            legend_labels,
            loc="upper center",
            bbox_to_anchor=(0.5, 0.965),
            ncol=min(len(legend_handles), 3),
            frameon=False,
        )
    fig.tight_layout()
    fig.subplots_adjust(top=0.90)
    output_pdf.parent.mkdir(parents=True, exist_ok=True)
    fig.savefig(output_pdf, format="pdf")
    plt.close(fig)


def main() -> None:
    variables = parse_bdt_variables(BDT_XML_FILE)
    variable_branches = [branch_for_variable(variable) for variable in variables]
    branches = [CLASS_BRANCH, *variable_branches]
    print(f"Loading event variables from {INPUT_ROOT_FILE}", flush=True)
    arrays = load_root_arrays(INPUT_ROOT_FILE, TREE_NAME, branches, MAX_EVENTS)

    print(f"Evaluating BDT response with {BDT_XML_FILE}", flush=True)
    scores = evaluate_bdt_response(
        INPUT_ROOT_FILE,
        TREE_NAME,
        BDT_XML_FILE,
        variables,
        MAX_EVENTS,
    )
    classes = scalar_array(arrays[CLASS_BRANCH]).astype(int)
    if scores.size != classes.size:
        raise RuntimeError(
            f"Score/event mismatch: got {scores.size} scores for {classes.size} events"
        )

    selected = np.isfinite(scores) & (scores > BDT_SCORE_CUT)
    selected_nc_mask = selected & (classes == NC_VALUE)
    selected_nc_full = (classes == NC_VALUE)

    bdm_samples: dict[str, tuple[dict[str, np.ndarray], np.ndarray]] = {}
    for label, sample_file in BDM_SAMPLE_FILES.items():
        sample_path = resolve_sample_path(sample_file, BDM_SAMPLE_DIR)
        print(f"Loading BDM sample {label} from {sample_path}", flush=True)
        sample_arrays = load_root_arrays(sample_path, TREE_NAME, variable_branches, MAX_EVENTS)
        print(f"Evaluating BDM BDT response for {label}", flush=True)
        sample_scores = evaluate_bdt_response(
            sample_path,
            TREE_NAME,
            BDT_XML_FILE,
            variables,
            MAX_EVENTS,
        )
        sample_n_events = len(values_for_variable(sample_arrays, variables[0]))
        if sample_scores.size != sample_n_events:
            raise RuntimeError(
                f"Score/event mismatch for {label}: got {sample_scores.size} scores "
                f"for {sample_n_events} events"
            )
        bdm_samples[label] = (sample_arrays, np.isfinite(sample_scores) & (sample_scores > BDT_SCORE_CUT))

    plot_selected_variables(
        arrays=arrays,
        variables=variables,
        nc_selected_mask=selected_nc_mask,
        nc_full_mask=selected_nc_full,
        bdm_samples=bdm_samples,
        output_pdf=OUTPUT_PDF,
    )

    print(f"XML: {BDT_XML_FILE}")
    print(f"Input ROOT: {INPUT_ROOT_FILE}")
    print(f"BDT score cut: response > {BDT_SCORE_CUT}")
    print(f"Total events read: {scores.size}")
    print(f"All NC events: {np.count_nonzero(selected_nc_full)}")
    print(f"Selected NC events: {np.count_nonzero(selected_nc_mask)}")
    for label, (_, selected_mask) in bdm_samples.items():
        print(f"Selected {label} events: {np.count_nonzero(selected_mask)}")
    print(f"Wrote: {OUTPUT_PDF}")


if __name__ == "__main__":
    main()
