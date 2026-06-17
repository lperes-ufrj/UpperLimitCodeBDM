from __future__ import annotations

import argparse
import os
from pathlib import Path
import subprocess
import sys
import time


DEFAULT_INPUT = (
    "/home/leoperes/ntuples_grid_newVertex/00a_newVertex/"
    "atm_all_Honda_hA_BR_solmax_NuFIT4p1_E40_cosZ20_1p5M_1M.root"
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Train the atmospheric CC/NC TMVA BDT.")
    parser.add_argument("--input-root", default=DEFAULT_INPUT, help="Input atmospheric ROOT file.")
    parser.add_argument("--tree", default="ana/Atm", help="Input TTree path.")
    parser.add_argument("--timestamp", default=None, help="Timestamp label for this run.")
    parser.add_argument(
        "--output-base",
        default=Path(__file__).resolve().parent / "outputs",
        type=Path,
        help="Base directory where timestamped run folders are created.",
    )
    parser.add_argument(
        "--_inside-log-wrapper",
        action="store_true",
        help=argparse.SUPPRESS,
    )
    return parser.parse_args()


def run_with_timestamped_log(args: argparse.Namespace) -> int:
    timestamp = args.timestamp or time.strftime("%Y%m%d%H%M")
    output_base = args.output_base.resolve()
    run_dir = output_base / f"BDT_{timestamp}"
    run_dir.mkdir(parents=True, exist_ok=True)

    log_file = run_dir / f"TMVA_training_{timestamp}.log"
    cmd = [
        sys.executable,
        str(Path(__file__).resolve()),
        "--input-root",
        str(args.input_root),
        "--tree",
        str(args.tree),
        "--timestamp",
        timestamp,
        "--output-base",
        str(output_base),
        "--_inside-log-wrapper",
    ]

    print(f"Saving BDT outputs to: {run_dir}")
    print(f"Saving TMVA training/test log to: {log_file}")

    with log_file.open("w", encoding="utf-8") as log:
        log.write(f"Command: {' '.join(cmd)}\n")
        log.write(f"Run directory: {run_dir}\n\n")
        log.flush()

        process = subprocess.Popen(
            cmd,
            cwd=str(run_dir),
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
            env=os.environ.copy(),
        )
        assert process.stdout is not None
        for line in process.stdout:
            sys.stdout.write(line)
            log.write(line)
        return process.wait()


def train_bdt(args: argparse.Namespace) -> None:
    import ROOT

    timestamp = args.timestamp or time.strftime("%Y%m%d%H%M")
    run_dir = args.output_base.resolve() / f"BDT_{timestamp}"
    run_dir.mkdir(parents=True, exist_ok=True)

    # Initialize TMVA
    ROOT.TMVA.Tools.Instance()

    # Open ROOT file with error checking
    stree = ROOT.TFile.Open(str(args.input_root))
    if not stree or stree.IsZombie():
        print(f"Error: Unable to open ROOT file at {args.input_root}")
        raise SystemExit(1)

    # Get tree
    tree = stree.Get(args.tree)
    if not tree:
        print(f"Error: Could not find tree '{args.tree}' in file.")
        raise SystemExit(1)

    # Define signal and background cuts
    sigCut = ROOT.TCut("CCNC == 1")  # Signal: Charged Current (CC)
    bgCut = ROOT.TCut("CCNC == 0")   # Background: Neutral Current (NC)

    # Print statistics
    print(f"Total Signal Events: {tree.GetEntries(sigCut.GetTitle())}")
    print(f"Total Background Events: {tree.GetEntries(bgCut.GetTitle())}")

    # Define output file with timestamp
    output_root = run_dir / f"BDT_{timestamp}_Atm.root"
    fout = ROOT.TFile(str(output_root), "RECREATE")

    # Define TMVA Factory
    factory = ROOT.TMVA.Factory(
        f"TMVAClassification_{timestamp}", fout,
        ":".join([
            "!V",               # Verbose off
            "!Silent",          # No batch mode silence
            "Color",            # Colored output
            "DrawProgressBar",  # Show training progress
            "Transformations=I;D;P;U;G,D",  # Input transformations
            "AnalysisType=Classification"
        ])
    )

    # Create DataLoader. TMVA writes weights/classes into this timestamped folder.
    dataloader = ROOT.TMVA.DataLoader(f"dataset_{timestamp}")

    # Define variables
    #dataloader.AddSpectator("event", "I")
    dataloader.AddVariable("PIDALongestTrack", "F") # PIDA of the longest track
    dataloader.AddVariable("nTracks", "I") # Number of tracks
    dataloader.AddVariable("nShowers", "I") # Number of showers
    dataloader.AddVariable("NHits", "I") # Number of 3D space points
    dataloader.AddVariable("log(HighestShowerSummedADC)", "F") # Highest Shower ADC
    dataloader.AddVariable("LargeShowerOpenAngle", "F") # Large shower opening angle
    dataloader.AddVariable("LongestShower", "F") # Longest shower in event
    #dataloader.AddVariable("CVN_NCScore", "F") # CVN score for NC
    dataloader.AddVariable("LongestTrack","F")
    dataloader.AddVariable("FracTotalChargeLongTrack", "F")

    # Add signal and background trees with cuts
    dataloader.AddSignalTree(tree, 1.0)
    dataloader.AddBackgroundTree(tree, 1.0)

    # Prepare dataset for training
    dataloader.PrepareTrainingAndTestTree(
        sigCut,
        bgCut,
        ":".join([
            "nTrain_Signal=155000",
            "nTrain_Background=580000",
            "SplitMode=Random",
            "NormMode=None",
            "!V"
        ])
    )

    # Book BDT method with optimized parameters
    factory.BookMethod(
        dataloader, ROOT.TMVA.Types.kBDT, f"BDTAtmCCNC_{timestamp}",
        ":".join([
        "!H", # Hide histograms in GUI
        "!V", # Disable verbosity
        "NTrees=250", # Number of trees
        "MinNodeSize=2.5%", # Minimum node size
        "MaxDepth=4", # Allow deeper trees
        "BoostType=AdaBoost", # Boosting type
        "AdaBoostBeta=0.5", # AdaBoost Beta
        "SeparationType=GiniIndex", # Gini Index
        "nCuts=50", # More cut steps for better feature splits
        "PruneMethod=NoPruning",
        "DoBoostMonitor=True"
        ])
    )
    # Train, test, and evaluate
    factory.TrainAllMethods()
    factory.TestAllMethods()
    factory.EvaluateAllMethods()

    fout.Close()
    stree.Close()

    print("TMVA training and evaluation completed successfully!")
    print(f"Output ROOT file: {output_root}")
    print(f"TMVA dataset folder: {run_dir / f'dataset_{timestamp}'}")


def main() -> None:
    args = parse_args()
    if not args._inside_log_wrapper:
        raise SystemExit(run_with_timestamped_log(args))
    train_bdt(args)


if __name__ == "__main__":
    main()
