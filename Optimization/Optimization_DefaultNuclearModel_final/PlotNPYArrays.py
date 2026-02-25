#!/usr/bin/env python3
"""
python3 PlotNPYArrays.py \
  --input-dir generated/20260216_170212
"""

from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt
import argparse


# -----------------------------
# Plotting function
# -----------------------------
def plot_npy_file(npy_file: Path, outdir: Path) -> None:

    try:
        arr = np.load(npy_file)

        if arr.size == 0:
            print(f"[WARN] Empty array: {npy_file.name}")
            return

        if arr.ndim != 1:
            print(f"[SKIP] Not 1D array: {npy_file.name}")
            return

        fig = plt.figure()

        plt.hist(arr, bins=100)

        plt.title(npy_file.stem)
        plt.xlabel("Value")
        plt.ylabel("Entries")

        outpath = outdir / (npy_file.stem + ".png")
        plt.savefig(outpath)

        plt.close(fig)

        print(f"[OK] Saved plot: {outpath.name}")

    except Exception as e:
        print(f"[ERROR] Failed for {npy_file.name}: {e}")


# -----------------------------
# Main
# -----------------------------
def main():

    parser = argparse.ArgumentParser(description="Plot all npy arrays in a directory")
    parser.add_argument(
        "--input-dir",
        required=True,
        type=Path,
        help="Path to generated/YYYYMMDD_HHMMSS folder",
    )

    args = parser.parse_args()

    input_dir = args.input_dir.resolve()

    if not input_dir.exists():
        raise RuntimeError(f"Directory does not exist: {input_dir}")

    npy_files = sorted(list(input_dir.glob("*.npy")))

    if len(npy_files) == 0:
        print("No .npy files found!")
        return

    plot_dir = input_dir / "plots"
    plot_dir.mkdir(exist_ok=True)

    print("\nSaving plots to:")
    print(plot_dir)
    print("\n")

    for npy in npy_files:
        plot_npy_file(npy, plot_dir)


if __name__ == "__main__":
    main()
