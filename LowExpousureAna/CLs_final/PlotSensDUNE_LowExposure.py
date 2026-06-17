#!/usr/bin/env python3
"""
Plot 100 kt-year and 400 kt-year sensitivity curves together.

This script mirrors the gamma-split plotting style from
CLs/CLs_final/PlotSensDUNE.ipynb, but reads the saved limits_*.dat files and
overlays:

  - 400 kt-year analysis (high exposure)
  - 100 kt-year analysis (low exposure)

Output files are written to plots/<timestamp>/ and each plot filename contains
the same timestamp.

Example:

  python3 PlotSensDUNE_LowExposure.py \
    --low-dir plots/20260512_223056 \
    --high-dir /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/CLs/CLs_final/plots/20260512_101630
"""

from __future__ import annotations

import argparse
from datetime import datetime
from pathlib import Path
from typing import Dict, Iterable, List, Tuple

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FixedLocator, NullLocator, ScalarFormatter

try:
    import dunestyle.matplotlib as dunestyle
except Exception:
    dunestyle = None


REPO_ROOT = Path(__file__).resolve().parents[2]
HIGH_EXPOSURE_PLOTS = REPO_ROOT / "CLs/CLs_final/plots"
LOW_EXPOSURE_PLOTS = Path(__file__).resolve().parent / "plots"

M_CHI = np.asarray([5.0, 10.0, 20.0, 40.0], dtype=np.float64)
GAMMAS = np.asarray([1.1, 1.5, 10.0], dtype=np.float64)
M_PSI = np.reshape(np.multiply.outer(GAMMAS, M_CHI), 12)

SAMPLE_TAGS = [
    "b1p1_m05", "b1p1_m10", "b1p1_m20", "b1p1_m40",
    "b1p5_m05", "b1p5_m10", "b1p5_m20", "b1p5_m40",
    "b10_m05", "b10_m10", "b10_m20", "b10_m40",
]

GAMMA_CONFIG = [
    ("1p1", r"$\gamma = 1.1$", slice(0, 4)),
    ("1p5", r"$\gamma = 1.5$", slice(4, 8)),
    ("10", r"$\gamma = 10$", slice(8, 12)),
]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Plot low-exposure DUNE sensitivity with high-exposure overlay."
    )
    parser.add_argument(
        "--low-dir",
        type=Path,
        default=None,
        help="Directory containing 100 kt-year limits_*.dat files. Defaults to latest complete low-exposure folder.",
    )
    parser.add_argument(
        "--high-dir",
        type=Path,
        default=None,
        help="Directory containing 400 kt-year limits_*.dat files. Defaults to latest complete high-exposure folder.",
    )
    parser.add_argument(
        "--output-base",
        type=Path,
        default=LOW_EXPOSURE_PLOTS,
        help="Base output directory for timestamped plot folder.",
    )
    parser.add_argument("--timestamp", default=None, help="Timestamp label for output files.")
    parser.add_argument("--formats", nargs="+", default=["pdf", "png"], help="Output formats.")
    return parser.parse_args()


def has_all_limit_files(path: Path) -> bool:
    return all((path / f"limits_{tag}.dat").exists() for tag in SAMPLE_TAGS)


def latest_complete_limits_dir(base: Path) -> Path:
    candidates = sorted(p for p in base.iterdir() if p.is_dir() and has_all_limit_files(p))
    if not candidates:
        raise FileNotFoundError(f"No complete limits folder found under {base}")
    return candidates[-1]


def load_limits(limit_dir: Path) -> np.ndarray:
    """
    Return array shape (5, 12):
      row 0 = -2 sigma
      row 1 = -1 sigma
      row 2 = central
      row 3 = +1 sigma
      row 4 = +2 sigma
    """
    columns: List[np.ndarray] = []
    for tag in SAMPLE_TAGS:
        filename = limit_dir / f"limits_{tag}.dat"
        if not filename.exists():
            raise FileNotFoundError(f"Missing limits file: {filename}")

        values = np.loadtxt(str(filename), delimiter=",")
        values = np.asarray(values, dtype=np.float64).reshape(-1)
        if values.size != 5:
            raise RuntimeError(f"{filename} has {values.size} values, expected 5")
        columns.append(values)

    return np.column_stack(columns)


def finite_positive(values: Iterable[np.ndarray]) -> np.ndarray:
    mask = None
    for arr in values:
        arr = np.asarray(arr)
        this = np.isfinite(arr) & (arr > 0)
        mask = this if mask is None else (mask & this)
    if mask is None:
        raise RuntimeError("No arrays provided for mask")
    return mask


def limits_ylim(low_limits: np.ndarray, high_limits: np.ndarray, slc: slice | None = None) -> Tuple[float, float]:
    low_values = low_limits if slc is None else low_limits[:, slc]
    high_values = high_limits if slc is None else high_limits[:, slc]
    vals = np.concatenate(
        [
            low_values.reshape(-1),
            high_values.reshape(-1),
        ]
    )
    vals = vals[np.isfinite(vals) & (vals > 0)]
    if vals.size == 0:
        return 1e-8, 1e-4
    return float(vals.min() * 0.65), float(vals.max() * 1.45)


def add_mchi_top_axis(ax, x_positions: np.ndarray) -> None:
    ax_top = ax.secondary_xaxis("top")
    ax_top.set_xscale("log")
    ax_top.set_xticks(x_positions)
    ax_top.set_xticklabels(["5", "10", "20", "40"])
    ax_top.set_xlabel(r"$m_\chi$ (GeV)", fontsize=15)
    ax_top.xaxis.set_minor_locator(NullLocator())
    ax_top.tick_params(axis="x", labelsize=11)


def plot_gamma(
    *,
    low_limits: np.ndarray,
    high_limits: np.ndarray,
    gamma_key: str,
    gamma_label: str,
    slc: slice,
    ylim: Tuple[float, float],
    outdir: Path,
    timestamp: str,
    formats: Iterable[str],
) -> None:
    x = M_PSI[slc]
    low = low_limits[:, slc]
    high = high_limits[:, slc]

    fig, ax = plt.subplots(figsize=(7.0, 5.5), dpi=150)

    c_high = "#1C77C3"
    c_high_band2 = "#8CB9DF"
    c_high_band1 = "#3E87C7"
    c_low = "#D65F00"
    c_low_band2 = "#F1B97A"
    c_low_band1 = "#E68613"
    sigma2_alpha = 0.55
    sigma1_alpha = 0.60

    high_mask = finite_positive([x, high[0], high[1], high[2], high[3], high[4]])
    low_mask = finite_positive([x, low[0], low[1], low[2], low[3], low[4]])

    if np.any(high_mask):
        ax.plot(
            x[high_mask], high[0][high_mask],
            lw=1.5, ls=":", color=c_high, alpha=sigma2_alpha, label=r"400 kt-year $\pm 2\sigma$",
        )
        ax.plot(
            x[high_mask], high[4][high_mask],
            lw=1.5, ls=":", color=c_high, alpha=sigma2_alpha,
        )
        ax.fill_between(
            x[high_mask], high[1][high_mask], high[3][high_mask],
            alpha=sigma1_alpha, color=c_high_band1, ec=None, label=r"400 kt-year $\pm 1\sigma$",
        )
        ax.plot(
            x[high_mask], high[2][high_mask],
            lw=3.0, ls="-", color=c_high, label="400 kt-year central",
        )

    if np.any(low_mask):
        ax.plot(
            x[low_mask], low[0][low_mask],
            lw=1.5, ls=":", color=c_low, alpha=sigma2_alpha, label=r"100 kt-year $\pm 2\sigma$",
        )
        ax.plot(
            x[low_mask], low[4][low_mask],
            lw=1.5, ls=":", color=c_low, alpha=sigma2_alpha,
        )
        ax.fill_between(
            x[low_mask], low[1][low_mask], low[3][low_mask],
            alpha=sigma1_alpha, color=c_low_band1, ec=None, label=r"100 kt-year $\pm 1\sigma$",
        )
        ax.plot(
            x[low_mask], low[2][low_mask],
            lw=3.2, ls="-", color=c_low, label="100 kt-year central",
        )

    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xlim(float(x.min() * 0.92), float(x.max() * 1.08))
    ax.set_ylim(*ylim)

    ax.set_xlabel(r"$m_\psi$ (GeV)", fontsize=17)
    ax.set_ylabel(r"$g_{Z^\prime}^4$ at 90% C.L.", fontsize=17)

    ax.xaxis.set_minor_locator(NullLocator())
    ax.xaxis.set_major_locator(FixedLocator(x))
    ax.get_xaxis().set_major_formatter(ScalarFormatter())
    ax.set_xticks(x)
    ax.set_xticklabels([f"{value:g}" for value in x])
    add_mchi_top_axis(ax, x)

    if dunestyle is not None:
        dunestyle.Simulation()

    ax.legend(title=gamma_label, frameon=True, fontsize=10, title_fontsize=14, ncols=2)
    ax.grid(which="both", linestyle=":", alpha=0.8)
    plt.tight_layout()

    for fmt in formats:
        filename = outdir / f"sensitivity_low_vs_high_gamma{gamma_key}_{timestamp}.{fmt}"
        fig.savefig(str(filename), dpi=600 if fmt.lower() in {"pdf", "png"} else None)

    plt.close(fig)


def main() -> None:
    args = parse_args()
    timestamp = args.timestamp or datetime.now().strftime("%Y%m%d_%H%M%S")

    low_dir = args.low_dir or latest_complete_limits_dir(LOW_EXPOSURE_PLOTS)
    high_dir = args.high_dir or latest_complete_limits_dir(HIGH_EXPOSURE_PLOTS)
    low_dir = low_dir.resolve()
    high_dir = high_dir.resolve()

    outdir = args.output_base.resolve() / timestamp
    outdir.mkdir(parents=True, exist_ok=True)

    print("\n========================================")
    print(f" Low exposure limits : {low_dir}")
    print(f" High exposure limits: {high_dir}")
    print(f" Saving plots to     : {outdir}")
    print("========================================\n")

    low_limits = load_limits(low_dir)
    high_limits = load_limits(high_dir)
    shared_ylim = limits_ylim(low_limits, high_limits)

    for gamma_key, gamma_label, slc in GAMMA_CONFIG:
        plot_gamma(
            low_limits=low_limits,
            high_limits=high_limits,
            gamma_key=gamma_key,
            gamma_label=gamma_label,
            slc=slc,
            ylim=shared_ylim,
            outdir=outdir,
            timestamp=timestamp,
            formats=args.formats,
        )

    print("Finished low-vs-high exposure sensitivity plots.")


if __name__ == "__main__":
    main()
