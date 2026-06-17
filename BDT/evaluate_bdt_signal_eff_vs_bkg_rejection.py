#!/usr/bin/env python3
"""Plot BDT signal efficiency vs atmospheric-neutrino background rejection.

The plot uses all events in each sample. There is no CVN/no-CVN split here:
the BDT response is treated as the only classifier.
"""

from __future__ import annotations

import argparse
import math
import os
import subprocess
import tempfile
import time
import warnings
import xml.etree.ElementTree as ET
from pathlib import Path

import numpy as np


SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_SAMPLE_DIR = Path("~/ntuples_grid_newVertex/00a_newVertex").expanduser()
DEFAULT_BACKGROUND = "atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M_1M.root"
DEFAULT_XML = (
    SCRIPT_DIR
    / "outputs/BDT_202605112035/dataset_202605112035/weights/TMVAClassification_202605112035_BDTAtmCCNC_202605112035.weights.xml"
)

# ADD MORE BDM SAMPLES HERE.
# Format: "legend_label": "root_file_name_or_full_path.root"
# Relative paths are resolved under --sample-dir.
BDM_SAMPLES = {
    r"$m_\chi = 5$ GeV, $\gamma = 1.1$": "bdm_m05_b1p1_00a.root",
    r"$m_\chi = 10$ GeV, $\gamma = 1.1$": "bdm_m10_b1p1_00a.root",
    r"$m_\chi = 20$ GeV, $\gamma = 1.1$": "bdm_m20_b1p1_00a.root",
    r"$m_\chi = 40$ GeV, $\gamma = 1.1$": "bdm_m40_b1p1_00a.root",
    r"$m_\chi = 5$ GeV, $\gamma = 1.5$": "bdm_m05_b1p5_00a.root",
    r"$m_\chi = 10$ GeV, $\gamma = 1.5$": "bdm_m10_b1p5_00a.root",
    r"$m_\chi = 20$ GeV, $\gamma = 1.5$": "bdm_m20_b1p5_00a.root",
    r"$m_\chi = 40$ GeV, $\gamma = 1.5$": "bdm_m40_b1p5_00a.root",
    r"$m_\chi = 5$ GeV, $\gamma = 10$": "bdm_m05_b10_00a.root",
    r"$m_\chi = 10$ GeV, $\gamma = 10$": "bdm_m10_b10_00a.root",
    r"$m_\chi = 20$ GeV, $\gamma = 10$": "bdm_m20_b10_00a.root",
    r"$m_\chi = 40$ GeV, $\gamma = 10$": "bdm_m40_b10_00a.root",
}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Plot BDT signal efficiency vs atmospheric-neutrino rejection."
    )
    parser.add_argument(
        "--sample-dir",
        type=Path,
        default=DEFAULT_SAMPLE_DIR,
        help=f"Directory containing ROOT ntuples. Default: {DEFAULT_SAMPLE_DIR}",
    )
    parser.add_argument(
        "--background",
        default=DEFAULT_BACKGROUND,
        help=f"Atmospheric-neutrino ROOT file. Default: {DEFAULT_BACKGROUND}",
    )
    parser.add_argument(
        "--tree",
        default="ana/Atm",
        help="TTree path inside each ROOT file. Default: ana/Atm",
    )
    parser.add_argument(
        "--xml",
        type=Path,
        default=DEFAULT_XML,
        help=f"TMVA weights XML. Default: {DEFAULT_XML}",
    )
    parser.add_argument(
        "--threshold-min",
        type=float,
        default=-0.2,
        help="Minimum BDT threshold. Default: -0.2",
    )
    parser.add_argument(
        "--threshold-max",
        type=float,
        default=1.0,
        help="Maximum BDT threshold. Default: 1.0",
    )
    parser.add_argument(
        "--n-thresholds",
        type=int,
        default=200,
        help="Number of BDT thresholds to scan. Default: 200",
    )
    parser.add_argument(
        "--plot-output",
        type=Path,
        default=SCRIPT_DIR / "bdt_signal_eff_vs_bkg_rejection.pdf",
        help="Output plot path. Default: BDT/bdt_signal_eff_vs_bkg_rejection.pdf",
    )
    parser.add_argument(
        "--max-events",
        type=int,
        default=None,
        help="Optional maximum events per sample, useful for quick tests.",
    )
    parser.add_argument(
        "--raw-shower-adc",
        action="store_true",
        help=(
            "Feed raw ADC to the XML variable named log(HighestShowerSummedADC). "
            "Default is log(max(adc, 1e-6)), matching the trained expression."
        ),
    )
    return parser.parse_args()


def resolve_path(path: Path | str, sample_dir: Path | None = None) -> Path:
    path = Path(path).expanduser()
    if not path.is_absolute() and sample_dir is not None:
        path = sample_dir / path
    return path.resolve()


def xml_variables(xml_file: Path) -> list[str]:
    root = ET.parse(xml_file).getroot()
    for variables in root.iter("Variables"):
        return [
            item.attrib["Expression"]
            for item in variables
            if "Expression" in item.attrib
        ]
    raise RuntimeError(f"No <Variables> block found in {xml_file}")


def cpp_string(value: Path | str) -> str:
    return str(value).replace("\\", "\\\\").replace('"', '\\"')


def evaluate_scores_with_root(
    root_file: Path,
    tree_name: str,
    xml_file: Path,
    variables: list[str],
    raw_shower_adc: bool,
    max_events: int | None,
) -> np.ndarray:
    """Evaluate the TMVA XML with ROOT's command-line C++ interpreter.

    This avoids importing PyROOT in Python, which can segfault in some shell
    environments while the ROOT executable itself works fine.
    """

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

    assignments = []
    for idx, variable in enumerate(variables):
        if raw_shower_adc and variable == "log(HighestShowerSummedADC)":
            assignments.append(
                f'    var_{idx} = static_cast<Float_t>(tree->GetLeaf("HighestShowerSummedADC")->GetValue());'
            )
        elif raw_shower_adc and variable == "log(HighestTrackSummedADC)":
            assignments.append(
                f'    var_{idx} = static_cast<Float_t>(tree->GetLeaf("HighestTrackSummedADC")->GetValue());'
            )
        else:
            assignments.append(
                f"    var_{idx} = static_cast<Float_t>(formula_{idx}.EvalInstance());"
            )
    assignment_block = "\n".join(assignments)

    with tempfile.TemporaryDirectory(prefix="bdt_scores_") as tmpdir:
        tmpdir = Path(tmpdir)
        macro_file = tmpdir / "evaluate_bdt_scores.C"
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

void evaluate_bdt_scores() {{
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
{assignment_block}
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
                "ROOT command-line BDT evaluation failed:\n"
                f"stdout:\n{result.stdout}\n"
                f"stderr:\n{result.stderr}"
            )

        scores = np.loadtxt(scores_file)
        return np.atleast_1d(scores).astype(float)


def efficiencies(scores: np.ndarray, thresholds: np.ndarray) -> np.ndarray:
    return np.array([(scores > threshold).sum() / scores.size for threshold in thresholds])


def import_pyplot():
    os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")
    warnings.filterwarnings("ignore", message="Unable to import Axes3D.*")

    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    return plt


def main() -> None:
    args = parse_args()

    sample_dir = args.sample_dir.expanduser().resolve()
    background_file = resolve_path(args.background, sample_dir)
    xml_file = resolve_path(args.xml)
    plot_output = resolve_path(args.plot_output)
    plot_output.parent.mkdir(parents=True, exist_ok=True)

    variables = xml_variables(xml_file)
    thresholds = np.linspace(args.threshold_min, args.threshold_max, args.n_thresholds)

    print(f"Using XML: {xml_file}")
    print(f"BDT variables: {', '.join(variables)}")
    print(f"Background: {background_file}")

    background_scores = evaluate_scores_with_root(
        background_file,
        args.tree,
        xml_file,
        variables,
        args.raw_shower_adc,
        args.max_events,
    )
    background_eff = efficiencies(background_scores, thresholds)
    background_rejection = 1.0 - background_eff
    print(f"Atmospheric neutrino events: {background_scores.size}")

    plt = import_pyplot()
    plt.figure(dpi=150, figsize=(7.2, 5.4))
    colors = plt.get_cmap("turbo")(np.linspace(0.05, 0.95, len(BDM_SAMPLES)))

    for color, (label, filename) in zip(colors, BDM_SAMPLES.items()):
        signal_file = resolve_path(filename, sample_dir)
        signal_scores = evaluate_scores_with_root(
            signal_file,
            args.tree,
            xml_file,
            variables,
            args.raw_shower_adc,
            args.max_events,
        )
        signal_eff = efficiencies(signal_scores, thresholds)
        plt.plot(signal_eff, background_rejection, color=color, lw=1.8, label=label)
        print(f"{label}: {signal_scores.size} events")
    x = np.linspace(0, 1, 10)
    plt.plot(x,1-x, color="gray", lw=1, ls="--")
    plt.xlabel("Signal efficiency (BDM)")
    plt.ylabel(r"Background rejection ($1 - \epsilon_{\mathrm{Atm}\nu}$)")
    plt.xlim(0.0, 1.0)
    plt.ylim(0.0, 1.0)
    plt.grid(alpha=0.25)
    plt.legend(fontsize=9, frameon=False)
    plt.tight_layout()
    plt.savefig(plot_output)

    print(f"Saved plot: {plot_output}")


if __name__ == "__main__":
    main()
