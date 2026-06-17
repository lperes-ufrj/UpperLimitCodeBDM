#!/usr/bin/env python3
"""
Calculate cos(theta) for reconstructed atmospheric neutrinos with respect to
the Sun direction.

This is the script version of the notebook logic:

    cos(theta_sun,reco) = TotalMomRecoRangeUnitVect . sampled_sun_position

For each reconstructed atmospheric neutrino event, one row is randomly sampled
from background_sun_pos.dat and dotted with the reconstructed momentum unit
vector from the ROOT branch " TotalMomRecoRangeUnitVect".

Example:

    python3 Optimization/Calc_AtmosphericCosThetaSun.py \
      --input-root /home/leoperes/reweighting_atmflux/reweight/atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M.root \
      --sun-pos-file Optimization/background_sun_pos.dat \
      --output Optimization/CosSun_Atm_hA_BR.npy \
      --plot Optimization/CosSun_Atm_hA_BR.png \
      --seed 12345
"""

from __future__ import annotations

import argparse
from pathlib import Path
from typing import Tuple

import numpy as np


def get_np_from_tree_raw(
    tree: ROOT.TTree,
    branch: str,
    estimate: int = 300_000_000,
) -> np.ndarray:
    """Read a ROOT branch with TTree.Draw and return a copied NumPy array."""
    tree.SetEstimate(int(estimate))
    n_values = tree.Draw(branch, "", "goff")
    return np.frombuffer(tree.GetV1(), dtype=np.float64, count=n_values).copy()


def get_tree(root_file: Path, tree_name: str) -> Tuple[ROOT.TFile, ROOT.TTree]:
    import ROOT

    root_file = Path(root_file)
    if not root_file.exists():
        raise FileNotFoundError(f"Input ROOT file not found: {root_file}")

    tfile = ROOT.TFile.Open(str(root_file))
    if not tfile or tfile.IsZombie():
        raise RuntimeError(f"Could not open ROOT file: {root_file}")

    tree = tfile.Get(tree_name)
    if not tree:
        raise KeyError(f"Tree '{tree_name}' not found in {root_file}")

    return tfile, tree


def load_sun_positions(sun_pos_file: Path) -> np.ndarray:
    sun_pos_file = Path(sun_pos_file)
    if not sun_pos_file.exists():
        raise FileNotFoundError(f"Sun position file not found: {sun_pos_file}")

    sun_positions = np.loadtxt(str(sun_pos_file), delimiter="\t", usecols=(0, 1, 2))
    sun_positions = np.asarray(sun_positions, dtype=np.float64)

    if sun_positions.ndim != 2 or sun_positions.shape[1] != 3:
        raise RuntimeError(f"Sun positions must have shape Nx3. Got {sun_positions.shape}")
    if len(sun_positions) == 0:
        raise RuntimeError(f"Sun position file is empty: {sun_pos_file}")

    return sun_positions


def normalize_rows(vectors: np.ndarray, label: str) -> np.ndarray:
    norms = np.linalg.norm(vectors, axis=1)
    if np.any(norms == 0):
        raise RuntimeError(f"{label} contains zero-length vectors")
    return vectors / norms[:, None]


def calculate_cos_theta_sun(
    reco_tree: ROOT.TTree,
    sun_positions: np.ndarray,
    rng: np.random.Generator,
    branch: str = " TotalMomRecoRangeUnitVect",
    normalize_vectors: bool = False,
) -> np.ndarray:
    mom = get_np_from_tree_raw(reco_tree, branch)
    n_reco = int(reco_tree.GetEntries())

    if mom.size != 3 * n_reco:
        raise RuntimeError(
            f"Unexpected size for {branch!r}: got {mom.size}, expected {3 * n_reco}"
        )

    reco_mom = np.reshape(mom, (n_reco, 3))
    if normalize_vectors:
        reco_mom = normalize_rows(reco_mom, "Reco momentum")
        sun_positions = normalize_rows(sun_positions, "Sun positions")

    sampled_indices = rng.integers(0, len(sun_positions), size=n_reco)
    sampled_sun_positions = sun_positions[sampled_indices]

    return np.einsum("ij,ij->i", reco_mom, sampled_sun_positions).astype(np.float64)


def save_histogram(cos_theta: np.ndarray, plot_file: Path, bins: int) -> None:
    import matplotlib.pyplot as plt

    plot_file = Path(plot_file)
    plot_file.parent.mkdir(parents=True, exist_ok=True)

    plt.figure(dpi=120)
    plt.hist(cos_theta, bins=bins, histtype="step")
    plt.ylabel("Number of Events")
    plt.xlabel(r"$cos(\theta_{Sun, Reco})$", fontsize=17)
    plt.tight_layout()
    plt.savefig(str(plot_file))
    plt.close()


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Calculate atmospheric-neutrino cos(theta) with respect to the Sun."
    )
    parser.add_argument("--input-root", required=True, type=Path, help="Atmospheric ROOT file.")
    parser.add_argument("--tree", default="ana/Atm", help="Reco tree name in the ROOT file.")
    parser.add_argument(
        "--branch",
        default=" TotalMomRecoRangeUnitVect",
        help='Momentum unit-vector branch. Default includes the leading space used in the ntuples.',
    )
    parser.add_argument(
        "--sun-pos-file",
        default=Path("Optimization/background_sun_pos.dat"),
        type=Path,
        help="Path to background_sun_pos.dat.",
    )
    parser.add_argument(
        "--output",
        default=Path("CosSun_Atm.npy"),
        type=Path,
        help="Output .npy file for the cos(theta) array.",
    )
    parser.add_argument("--output-txt", type=Path, help="Optional text output for the cos(theta) array.")
    parser.add_argument("--plot", type=Path, help="Optional histogram image output path.")
    parser.add_argument("--bins", default=20, type=int, help="Number of histogram bins.")
    parser.add_argument("--seed", default=12345, type=int, help="Random seed for Sun-position sampling.")
    parser.add_argument(
        "--normalize-vectors",
        action="store_true",
        help="Normalize reco and Sun vectors before taking the dot product.",
    )
    args = parser.parse_args()

    rng = np.random.default_rng(args.seed)
    sun_positions = load_sun_positions(args.sun_pos_file)
    root_handle, reco_tree = get_tree(args.input_root, args.tree)

    try:
        cos_theta = calculate_cos_theta_sun(
            reco_tree=reco_tree,
            sun_positions=sun_positions,
            rng=rng,
            branch=args.branch,
            normalize_vectors=args.normalize_vectors,
        )
    finally:
        root_handle.Close()

    args.output.parent.mkdir(parents=True, exist_ok=True)
    np.save(str(args.output), cos_theta)

    if args.output_txt:
        args.output_txt.parent.mkdir(parents=True, exist_ok=True)
        np.savetxt(str(args.output_txt), cos_theta)

    if args.plot:
        save_histogram(cos_theta, args.plot, args.bins)

    print(f"Saved {len(cos_theta)} cos(theta_sun,reco) values to {args.output}")
    print(
        "Summary: "
        f"min={np.min(cos_theta):.6g}, "
        f"max={np.max(cos_theta):.6g}, "
        f"mean={np.mean(cos_theta):.6g}, "
        f"std={np.std(cos_theta):.6g}"
    )


if __name__ == "__main__":
    main()
