#!/usr/bin/env python3
"""Plot the TMVA BDT response for atmospheric CC and NC events."""

from __future__ import annotations

import argparse
import os
import warnings
import xml.etree.ElementTree as ET
from dataclasses import dataclass
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

ATMOSPHERIC_NU_ROOT_FILE = (
    "/home/leoperes/ntuples_grid_newVertex/00a_newVertex/"
    "atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M_500k.root"
)

BDT_XML_FILE = (
    "/home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/"
    "BDT/outputs/BDT_202605112035/dataset_202605112035/weights/"
    "TMVAClassification_202605112035_BDTAtmCCNC_202605112035.weights.xml"
)

# Add or edit BDM samples here.
# The dictionary key is the legend label. The value can be either:
#   1. a full path to a ROOT file, or
#   2. a file name relative to BDM_SAMPLE_DIR.
BDM_SAMPLE_DIR = Path("~/ntuples_grid_newVertex/00a_newVertex").expanduser()
BDM_SAMPLE_FILES = {
    r"$m_\chi = 5$ GeV, $\gamma = 1.1$": "bdm_m05_b1p1_00a.root",
    r"$m_\chi = 10$ GeV, $\gamma = 1.1$": "bdm_m10_b1p1_00a.root",
    r"$m_\chi = 20$ GeV, $\gamma = 1.1$": "bdm_m20_b1p1_00a.root",
    r"$m_\chi = 40$ GeV, $\gamma = 1.1$": "bdm_m40_b1p1_00a.root"
}


@dataclass(frozen=True)
class BDTNode:
    ivar: int
    cut: float
    ctype: bool
    ntype: int
    left: "BDTNode | None" = None
    right: "BDTNode | None" = None


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Read an atmospheric ROOT file with uproot and plot the BDT response for truth CC/NC."
    )
    parser.add_argument(
        "--atm-root",
        type=Path,
        default=Path(ATMOSPHERIC_NU_ROOT_FILE),
        help=f"Atmospheric-neutrino ROOT file. Default: {ATMOSPHERIC_NU_ROOT_FILE}",
    )
    parser.add_argument(
        "--bdm-sample-dir",
        type=Path,
        default=BDM_SAMPLE_DIR,
        help=f"Directory for relative BDM file names. Default: {BDM_SAMPLE_DIR}",
    )
    parser.add_argument(
        "--no-bdm",
        action="store_true",
        help="Only plot atmospheric CC/NC, skipping the BDM samples listed in BDM_SAMPLE_FILES.",
    )
    parser.add_argument(
        "--tree",
        default="ana/Atm",
        help="TTree path inside the ROOT file. Default: ana/Atm",
    )
    parser.add_argument(
        "--variables",
        nargs="+",
        default=None,
        help="BDT input expressions. Default: read from --xml.",
    )
    parser.add_argument(
        "--xml",
        type=Path,
        default=Path(BDT_XML_FILE),
        help=f"TMVA weights XML used to get default BDT variables. Default: {BDT_XML_FILE}",
    )
    parser.add_argument(
        "--class-branch",
        default="CCNC",
        help="Branch used to split samples. Default: CCNC",
    )
    parser.add_argument(
        "--cc-value",
        type=int,
        default=0,
        help="Truth CC value in --class-branch. Default: 0",
    )
    parser.add_argument(
        "--nc-value",
        type=int,
        default=1,
        help="Truth NC value in --class-branch. Default: 1",
    )
    parser.add_argument(
        "--bins",
        type=int,
        default=60,
        help="Histogram bins. Default: 60",
    )
    parser.add_argument(
        "--max-events",
        type=int,
        default=None,
        help="Optional maximum number of events to read.",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=Path(__file__).resolve().parent / "BDT_response_CCNC.pdf",
        help="Output plot path. Default: ValidationStudies/BDT_response_CCNC.pdf",
    )
    parser.add_argument(
        "--list-branches",
        action="store_true",
        help="Print available tree branches and exit.",
    )
    return parser.parse_args()


def parse_node(element: ET.Element) -> BDTNode:
    children = {child.attrib.get("pos"): child for child in element.findall("Node")}
    left = parse_node(children["l"]) if "l" in children else None
    right = parse_node(children["r"]) if "r" in children else None
    return BDTNode(
        ivar=int(element.attrib["IVar"]),
        cut=float(element.attrib["Cut"]),
        ctype=bool(int(element.attrib["cType"])),
        ntype=int(element.attrib["nType"]),
        left=left,
        right=right,
    )


def parse_bdt_xml(xml_file: Path) -> tuple[list[str], list[tuple[float, BDTNode]]]:
    xml_file = xml_file.expanduser().resolve()
    if not xml_file.exists():
        raise FileNotFoundError(f"TMVA weights XML not found: {xml_file}")

    root = ET.parse(xml_file).getroot()
    expressions: list[str] | None = None
    for variables in root.iter("Variables"):
        expressions = [
            item.attrib["Expression"]
            for item in variables
            if "Expression" in item.attrib
        ]
        break
    if not expressions:
        raise RuntimeError(f"No <Variables> block found in {xml_file}")

    trees = []
    weights = root.find("Weights")
    if weights is None:
        raise RuntimeError(f"No <Weights> block found in {xml_file}")
    for binary_tree in weights.findall("BinaryTree"):
        root_node = binary_tree.find("Node")
        if root_node is None:
            continue
        trees.append((float(binary_tree.attrib["boostWeight"]), parse_node(root_node)))
    if not trees:
        raise RuntimeError(f"No BDT trees found in {xml_file}")

    return expressions, trees


def branch_for_variable(variable: str) -> str:
    if variable.startswith("log(") and variable.endswith(")"):
        return variable[4:-1].strip()
    return variable


def values_for_variable(arrays: dict[str, np.ndarray], variable: str) -> np.ndarray:
    branch = branch_for_variable(variable)
    values = scalar_array(arrays[branch])
    if variable.startswith("log(") and variable.endswith(")"):
        values = np.log(np.clip(values.astype(np.float64), 1.0e-6, None))
    return values


def scalar_array(values: np.ndarray) -> np.ndarray:
    values = np.asarray(values)
    if values.dtype != object:
        return values.reshape(-1)

    out = np.empty(len(values), dtype=np.float64)
    for idx, item in enumerate(values):
        item = np.asarray(item).reshape(-1)
        out[idx] = item[0] if item.size else np.nan
    return out


def resolve_sample_path(path: str | Path, base_dir: Path | None = None) -> Path:
    path = Path(path).expanduser()
    if not path.is_absolute() and base_dir is not None:
        path = base_dir.expanduser() / path
    return path.resolve()


def load_root_arrays(
    root_file: Path,
    tree_name: str,
    branches: list[str],
    max_events: int | None,
    list_branches: bool = False,
) -> dict[str, np.ndarray]:
    root_file = root_file.expanduser().resolve()
    if not root_file.exists():
        raise FileNotFoundError(f"Input ROOT file not found: {root_file}")

    with uproot.open(root_file) as handle:
        if tree_name not in handle:
            available = ", ".join(handle.keys())
            raise KeyError(f"Tree '{tree_name}' not found in {root_file}. Keys: {available}")
        tree = handle[tree_name]

        if list_branches:
            print("\n".join(tree.keys()))
            raise SystemExit(0)

        branches = list(dict.fromkeys(branches))
        missing = [branch for branch in branches if branch not in tree.keys()]
        if missing:
            raise KeyError(f"Missing branch(es) in {tree_name}: {', '.join(missing)}")

        return tree.arrays(
            branches,
            library="np",
            entry_stop=max_events,
        )


def evaluate_tree(
    node: BDTNode,
    inputs: np.ndarray,
    output: np.ndarray,
    indices: np.ndarray,
) -> None:
    if indices.size == 0:
        return

    if node.ntype != 0 or node.left is None or node.right is None:
        output[indices] = float(node.ntype)
        return

    values = inputs[node.ivar, indices]
    goes_right = values > node.cut
    if not node.ctype:
        goes_right = ~goes_right

    evaluate_tree(node.left, inputs, output, indices[~goes_right])
    evaluate_tree(node.right, inputs, output, indices[goes_right])


def evaluate_bdt_response(
    arrays: dict[str, np.ndarray],
    variables: list[str],
    trees: list[tuple[float, BDTNode]],
) -> np.ndarray:
    inputs = np.vstack([values_for_variable(arrays, variable) for variable in variables])
    n_events = inputs.shape[1]
    indices = np.arange(n_events)
    response = np.zeros(n_events, dtype=np.float64)
    weight_sum = 0.0

    for weight, root_node in trees:
        tree_output = np.zeros(n_events, dtype=np.float64)
        evaluate_tree(root_node, inputs, tree_output, indices)
        response += weight * tree_output
        weight_sum += weight

    if weight_sum == 0.0:
        raise RuntimeError("BDT XML has zero total boost weight.")
    return response / weight_sum


def plot_bdt_response(
    atm_scores: np.ndarray,
    atm_cc_mask: np.ndarray,
    atm_nc_mask: np.ndarray,
    bdm_scores_by_label: dict[str, np.ndarray],
    bins: int,
    output: Path,
) -> None:
    cc_scores = atm_scores[atm_cc_mask]
    nc_scores = atm_scores[atm_nc_mask]
    bin_edges = np.linspace(-0.8, 0.8, bins + 1)

    fig, ax = plt.subplots(dpi=150)
    ax.hist(
        nc_scores,
        bins=bin_edges,
        histtype="step",
        density=True,
        linewidth=1.7,
        label=rf" Atm-$\nu$ Truth NC",# ({nc_scores.size})",
        color="tab:blue",
    )
    ax.hist(
        cc_scores,
        bins=bin_edges,
        histtype="step",
        density=True,
        linewidth=1.7,
        label=rf" Atm-$\nu$ Truth CC",# ({cc_scores.size})",
        color="tab:red",
    )

    colors = plt.cm.viridis(np.linspace(0.08, 0.92, max(len(bdm_scores_by_label), 1)))
    for color, (label, sample_scores) in zip(colors, bdm_scores_by_label.items()):
        ax.hist(
            sample_scores,
            bins=bin_edges,
            histtype="step",
            density=True,
            linewidth=1.2,
            label=f"{label}",# ({sample_scores.size})",
            color=color,
            alpha=0.9,
        )

    ax.set_xlabel("BDT NC Score")
    ax.set_ylabel("Frequency Normalized")
    ax.set_xlim(bin_edges[0], bin_edges[-1])
    ax.grid(alpha=0.25)
    if dunestyle is not None:
        dunestyle.Simulation(0.45, 0.9)
    ax.legend(frameon=True)
    fig.tight_layout()
    fig.savefig(output)
    plt.close(fig)


def main() -> None:
    args = parse_args()
    xml_variables, trees = parse_bdt_xml(args.xml)
    if args.variables is None:
        args.variables = xml_variables
        print(f"Using BDT variables from XML: {args.xml.expanduser().resolve()}")

    bdt_branches = [branch_for_variable(variable) for variable in args.variables]
    atm_branches = [args.class_branch, *bdt_branches]

    atm_arrays = load_root_arrays(
        root_file=args.atm_root,
        tree_name=args.tree,
        branches=atm_branches,
        max_events=args.max_events,
        list_branches=args.list_branches,
    )
    atm_scores = evaluate_bdt_response(atm_arrays, args.variables, trees)

    classes = scalar_array(atm_arrays[args.class_branch]).astype(int)
    atm_cc_mask = classes == args.cc_value
    atm_nc_mask = classes == args.nc_value

    bdm_scores_by_label = {}
    if not args.no_bdm:
        for label, sample_file in BDM_SAMPLE_FILES.items():
            sample_path = resolve_sample_path(sample_file, args.bdm_sample_dir)
            sample_arrays = load_root_arrays(
                root_file=sample_path,
                tree_name=args.tree,
                branches=bdt_branches,
                max_events=args.max_events,
            )
            bdm_scores_by_label[label] = evaluate_bdt_response(
                sample_arrays,
                args.variables,
                trees,
            )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    plot_bdt_response(
        atm_scores=atm_scores,
        atm_cc_mask=atm_cc_mask,
        atm_nc_mask=atm_nc_mask,
        bdm_scores_by_label=bdm_scores_by_label,
        bins=args.bins,
        output=args.output,
    )

    print(f"Wrote {args.output}")
    print(f"Atmospheric truth CC events: {np.count_nonzero(atm_cc_mask)}")
    print(f"Atmospheric truth NC events: {np.count_nonzero(atm_nc_mask)}")
    for label, scores in bdm_scores_by_label.items():
        print(f"BDM {label}: {scores.size} events")


if __name__ == "__main__":
    main()
