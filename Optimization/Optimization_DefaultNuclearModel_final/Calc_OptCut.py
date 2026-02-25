#!/usr/bin/env python3
"""
Calc_OptCut.py

Same logic as before, but now ANY output file that is "just an array"
is saved as .npy instead of .txt.

The summary tables (Sensitivity_Info_*.txt, Sensitivity_results_*.txt,
Eff_Bkg_index_*.txt) stay as .txt (because they are human-readable tables).


python3 Calc_OptCut.py \
  --base-path /home/leoperes/ \
  --sun-pos-file ../background_sun_pos.dat \
  --weights-xml /home/leoperes/Desktop/UpperLimitCodeBDM_final/UpperLimitCodeBDM/BDT/dataset/weights/TMVAClassification_BDTAtmCCNC_202601261224.weights.xml \
  --seed 12345

"""

from __future__ import annotations

from datetime import datetime
import argparse
import math
from pathlib import Path
from typing import List, Tuple

import numpy as np
import ROOT
from array import array


# -----------------------------
# Utilities
# -----------------------------
def save_npy(arr: np.ndarray, filename: Path) -> None:
    """
    Save numpy array in binary .npy format.
    """
    filename.parent.mkdir(parents=True, exist_ok=True)
    arr = np.asarray(arr)
    np.save(str(filename), arr)


def get_np_from_tree(tree: ROOT.TTree, branch: str, estimate: int = 3_000_000) -> np.ndarray:
    tree.SetEstimate(int(estimate))
    n = tree.Draw(branch, "", "goff")
    out = np.frombuffer(tree.GetV1(), dtype=np.float64, count=n).copy()
    return out


def get_np_from_tree_raw(tree: ROOT.TTree, branch: str, estimate: int = 300_000_000) -> np.ndarray:
    tree.SetEstimate(int(estimate))
    n = tree.Draw(branch, "", "goff")
    out = np.frombuffer(tree.GetV1(), count=n).copy()
    return out


def create_run_output_dir(base: str = "generated") -> Path:
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    run_dir = Path.cwd() / base / timestamp
    run_dir.mkdir(parents=True, exist_ok=True)

    print("\n========================================")
    print(f" Saving outputs to:\n {run_dir}")
    print("========================================\n")
    return run_dir


def write_header(fh, header: str) -> None:
    fh.write(header + "\n\n")


# -----------------------------
# TMVA BDT response
# -----------------------------
def get_bdt_response(
    tree: ROOT.TTree,
    weights_xml: Path,
) -> np.ndarray:
    """
    Compute TMVA BDT response for ALL events in the tree.
    Returns length == tree.GetEntries()
    """
    weights_xml = Path(weights_xml)
    if not weights_xml.exists():
        raise FileNotFoundError(f"TMVA weights XML not found: {weights_xml}")

    ROOT.TMVA.Tools.Instance()
    reader = ROOT.TMVA.Reader("!Color:!Silent")

    PIDALongestTrack = array("f", [0.0])
    nTracks = array("f", [0.0])
    nShowers = array("f", [0.0])
    NHits = array("f", [0.0])
    HighestShowerSummedADC = array("f", [0.0])
    LargeShowerOpenAngle = array("f", [0.0])
    LongestShower = array("f", [0.0])
    LongestTrack = array("f", [0.0])
    FracTotalChargeLongTrack = array("f", [0.0])

    reader.AddVariable("PIDALongestTrack", PIDALongestTrack)
    reader.AddVariable("nTracks", nTracks)
    reader.AddVariable("nShowers", nShowers)
    reader.AddVariable("NHits", NHits)
    reader.AddVariable("log(HighestShowerSummedADC)", HighestShowerSummedADC)
    reader.AddVariable("LargeShowerOpenAngle", LargeShowerOpenAngle)
    reader.AddVariable("LongestShower", LongestShower)
    reader.AddVariable("LongestTrack", LongestTrack)
    reader.AddVariable("FracTotalChargeLongTrack", FracTotalChargeLongTrack)

    reader.BookMVA("TMVAClassification", str(weights_xml))

    out: List[float] = []
    nentry = tree.GetEntries()

    for i in range(nentry):
        tree.GetEntry(i)

        PIDALongestTrack[0] = float(tree.PIDALongestTrack)
        nTracks[0] = float(tree.nTracks)
        nShowers[0] = float(tree.nShowers)
        NHits[0] = float(tree.NHits)
        HighestShowerSummedADC[0] = float(tree.HighestShowerSummedADC)
        LargeShowerOpenAngle[0] = float(tree.LargeShowerOpenAngle)
        LongestShower[0] = float(tree.LongestShower)
        LongestTrack[0] = float(tree.LongestTrack)
        FracTotalChargeLongTrack[0] = float(tree.FracTotalChargeLongTrack)

        out.append(float(reader.EvaluateMVA("TMVAClassification")))

    return np.asarray(out, dtype=np.float64)


# -----------------------------
# Scan functions (new logic)
# -----------------------------
def scan_best_cuts_bdt_only(
    *,
    bdt_cut: float,
    cos_right_grid: np.ndarray,
    cos_left_grid: np.ndarray,
    n_signal_simulated: int,
    bdt_signal: np.ndarray,
    bdt_atm: np.ndarray,
    cos_signal: np.ndarray,
    cos_atm: np.ndarray,
    background_scale: float,
) -> List:
    """
    BDT + angular cuts only. CVN ignored.
    Returns:
      [SprimeMin, bestCutLeft, bestCutRight, bestEff, bestBkg, bestBkgErr, bdt_cut, cos_sig_all, cos_atm_all]
    """
    sig_mask_bdt = bdt_signal > bdt_cut
    bkg_mask_bdt = bdt_atm > bdt_cut

    cos_sig_all = cos_signal[sig_mask_bdt]
    cos_atm_all = cos_atm[bkg_mask_bdt]

    if n_signal_simulated <= 0:
        return [np.inf, np.nan, np.nan, 0.0, np.inf, np.inf, bdt_cut, cos_sig_all, cos_atm_all]

    sprime_min = np.inf
    best_right = np.nan
    best_left = np.nan
    best_eff = 0.0
    best_bkg = np.inf
    best_bkg_err = np.inf

    for cr in cos_right_grid:
        for cl in cos_left_grid:
            n_sig = np.sum(cos_sig_all > cr) + np.sum(cos_sig_all < cl)
            r_reco = n_sig / float(n_signal_simulated)
            if r_reco <= 0:
                continue

            n_bkg = np.sum(cos_atm_all > cr) + np.sum(cos_atm_all < cl)
            b_events = n_bkg * background_scale

            sprime = 25.0 / (2.0 * r_reco) + math.sqrt(
                25.0 * b_events / (r_reco * r_reco) + 625.0 / (4.0 * r_reco * r_reco)
            )

            if sprime < sprime_min:
                sprime_min = sprime
                best_right = float(cr)
                best_left = float(cl)
                best_eff = float(r_reco)
                best_bkg = float(b_events)
                best_bkg_err = float(math.sqrt(max(n_bkg, 0.0) * background_scale))

    return [sprime_min, best_left, best_right, best_eff, best_bkg, best_bkg_err, bdt_cut, cos_sig_all, cos_atm_all]


def scan_best_cuts_cvn_only(
    *,
    cvn_cut: float,
    cos_right_grid: np.ndarray,
    cos_left_grid: np.ndarray,
    n_signal_simulated: int,
    cvn_signal: np.ndarray,
    cvn_atm: np.ndarray,
    cos_signal: np.ndarray,
    cos_atm: np.ndarray,
    background_scale: float,
) -> List:
    """
    CVN + angular cuts only. Drop CVN == -1 events entirely.
    Returns:
      [SprimeMin, bestCutLeft, bestCutRight, bestEff, bestBkg, bestBkgErr, cvn_cut, cos_sig_all, cos_atm_all]
    """
    sig_valid = cvn_signal > -1
    atm_valid = cvn_atm > -1

    cvn_signal_v = cvn_signal[sig_valid]
    cos_signal_v = cos_signal[sig_valid]
    cvn_atm_v = cvn_atm[atm_valid]
    cos_atm_v = cos_atm[atm_valid]

    sig_mask = cvn_signal_v > cvn_cut
    bkg_mask = cvn_atm_v > cvn_cut

    cos_sig_all = cos_signal_v[sig_mask]
    cos_atm_all = cos_atm_v[bkg_mask]

    if n_signal_simulated <= 0:
        return [np.inf, np.nan, np.nan, 0.0, np.inf, np.inf, cvn_cut, cos_sig_all, cos_atm_all]

    sprime_min = np.inf
    best_right = np.nan
    best_left = np.nan
    best_eff = 0.0
    best_bkg = np.inf
    best_bkg_err = np.inf

    for cr in cos_right_grid:
        for cl in cos_left_grid:
            n_sig = np.sum(cos_sig_all > cr) + np.sum(cos_sig_all < cl)
            r_reco = n_sig / float(n_signal_simulated)
            if r_reco <= 0:
                continue

            n_bkg = np.sum(cos_atm_all > cr) + np.sum(cos_atm_all < cl)
            b_events = n_bkg * background_scale

            sprime = 25.0 / (2.0 * r_reco) + math.sqrt(
                25.0 * b_events / (r_reco * r_reco) + 625.0 / (4.0 * r_reco * r_reco)
            )

            if sprime < sprime_min:
                sprime_min = sprime
                best_right = float(cr)
                best_left = float(cl)
                best_eff = float(r_reco)
                best_bkg = float(b_events)
                best_bkg_err = float(math.sqrt(max(n_bkg, 0.0) * background_scale))

    return [sprime_min, best_left, best_right, best_eff, best_bkg, best_bkg_err, cvn_cut, cos_sig_all, cos_atm_all]


# -----------------------------
# IO: samples
# -----------------------------
def open_samples(base_path: Path, subdir: str = "ntuples_grid_newVertex/00a_newVertex") -> List[ROOT.TFile]:
    base_path = Path(base_path)
    root_dir = base_path / subdir

    files = [
        root_dir / "atm_hA_BR_4ana.root",
        root_dir / "bdm_m05_b1p1_00a.root",
        root_dir / "bdm_m10_b1p1_00a.root",
        root_dir / "bdm_m20_b1p1_00a.root",
        root_dir / "bdm_m40_b1p1_00a.root",
        root_dir / "bdm_m05_b1p5_00a.root",
        root_dir / "bdm_m10_b1p5_00a.root",
        root_dir / "bdm_m20_b1p5_00a.root",
        root_dir / "bdm_m40_b1p5_00a.root",
        root_dir / "bdm_m05_b10_00a.root",
        root_dir / "bdm_m10_b10_00a.root",
        root_dir / "bdm_m20_b10_00a.root",
        root_dir / "bdm_m40_b10_00a.root",
    ]

    out: List[ROOT.TFile] = []
    for f in files:
        if not f.exists():
            raise FileNotFoundError(f"Missing ROOT file: {f}")
        tf = ROOT.TFile.Open(str(f))
        if not tf or tf.IsZombie():
            raise RuntimeError(f"Failed to open ROOT file: {f}")
        out.append(tf)
    return out


def get_tree(tf: ROOT.TFile, name: str) -> ROOT.TTree:
    t = tf.Get(name)
    if not t:
        raise KeyError(f"Tree '{name}' not found in file {tf.GetName()}")
    return t


# -----------------------------
# Atmospheric cos(theta_sun)
# -----------------------------
def build_atmospheric_cos_sun(
    reco_tree: ROOT.TTree,
    sun_pos_file: Path,
    rng: np.random.Generator,
) -> Tuple[np.ndarray, int]:
    sun_pos_file = Path(sun_pos_file)
    if not sun_pos_file.exists():
        raise FileNotFoundError(f"Sun position file not found: {sun_pos_file}")

    mom = get_np_from_tree_raw(reco_tree, " TotalMomRecoRangeUnitVect", estimate=300_000_000)
    n_reco = reco_tree.GetEntries()
    if mom.size != 3 * n_reco:
        raise RuntimeError(
            f"Unexpected size for TotalMomRecoRangeUnitVect: got {mom.size}, expected {3*n_reco}"
        )

    reco_mom = np.reshape(mom, (n_reco, 3))

    sun_positions = np.loadtxt(str(sun_pos_file), delimiter="\t", usecols=(0, 1, 2))
    if sun_positions.ndim != 2 or sun_positions.shape[1] != 3:
        raise RuntimeError(f"Sun positions must be Nx3. Got shape={sun_positions.shape}")

    idx = rng.integers(0, len(sun_positions), size=n_reco)
    sun = sun_positions[idx]

    cos = np.einsum("ij,ij->i", reco_mom, sun).astype(np.float64)
    return cos, n_reco


# -----------------------------
# Main
# -----------------------------
def main() -> None:
    parser = argparse.ArgumentParser(description="Scan optimal cuts with per-sample logic (BDT-only vs CVN-only).")
    parser.add_argument("--base-path", required=True, type=Path, help="Base path containing ntuples_grid_newVertex/...")
    parser.add_argument(
        "--subdir",
        default="ntuples_grid_newVertex/00a_newVertex",
        help="Subdirectory under base-path containing the ROOT ntuples.",
    )
    parser.add_argument("--sun-pos-file", required=True, type=Path, help="Path to background_sun_pos.dat")
    parser.add_argument("--weights-xml", required=True, type=Path, help="TMVA weights XML for the BDT.")
    parser.add_argument("--seed", default=12345, type=int, help="RNG seed for sun-position sampling.")
    parser.add_argument("--append", action="store_true", help="Append to output summary files instead of overwriting.")
    args = parser.parse_args()

    outdir = create_run_output_dir()
    rng = np.random.default_rng(args.seed)

    files = open_samples(args.base_path, subdir=args.subdir)
    reco_trees = [get_tree(tf, "ana/Atm") for tf in files]
    simu_trees = [get_tree(tf, "ana/AllEvents") for tf in files]
    reco_entries = [t.GetEntries() for t in reco_trees]
    simu_entries = [t.GetEntries() for t in simu_trees]

    # ---------- Atmosphere ----------
    atm_reco_tree = reco_trees[0]
    atm_simu_tree = simu_trees[0]

    cos_atm, n_reco_atm = build_atmospheric_cos_sun(atm_reco_tree, args.sun_pos_file, rng)
    n_sim_atm = atm_simu_tree.GetEntries()
    ratio_reco_atm = n_reco_atm / float(n_sim_atm)

    cvn_atm = get_np_from_tree(atm_reco_tree, "CVN_NCScore", estimate=3_000_000)

    # Only needed for BDT-only group (index0 < 4)
    bdt_atm_all = get_bdt_response(atm_reco_tree, args.weights_xml)

    background_scale = 4.0 * 10.0 * 2495.98 / float(n_sim_atm)

    # ---------- Output files ----------
    mode = "a" if args.append else "w"
    f_info = open(outdir / "Sensitivity_Info_00a.txt", mode)
    f_results = open(outdir / "Sensitivity_results_00a.txt", mode)
    f_effbkg = open(outdir / "Eff_Bkg_index_00a.txt", mode)

    write_header(f_info, "################# SAMPLE INFO #######################")
    f_info.write(f"Number of Atmospheric Neutrinos Events Simulated: {n_sim_atm}\n")
    f_info.write(f"Number of Atmospheric Neutrinos Events Reconstructed: {n_reco_atm}\n")
    f_info.write(f"Ratio of Atmospheric Neutrinos Events Reconstructed: {ratio_reco_atm}\n\n")

    # diagnostics (arrays -> .npy)
    save_npy(cvn_atm, outdir / "CVN_Atm_hA_BR.npy")
    save_npy(cos_atm, outdir / "CosSun_Atm_hA_BR.npy")
    save_npy(bdt_atm_all, outdir / "BDT_Atm_hA_BR_ALL.npy")

    if not args.append:
        f_effbkg.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tCutValue\n")

    list_samples = [
        "m05_b1p1", "m10_b1p1", "m20_b1p1", "m40_b1p1",
        "m05_b1p5", "m10_b1p5", "m20_b1p5", "m40_b1p5",
        "m05_b10", "m10_b10", "m20_b10", "m40_b10",
    ]

    # ---------- Scan signal samples ----------
    for sig_idx, sig_reco_tree in enumerate(reco_trees[1:], start=1):
        index0 = sig_idx - 1
        out_tag = list_samples[index0] if index0 < len(list_samples) else f"sig{sig_idx:02d}"

        cvn_sig = get_np_from_tree(sig_reco_tree, "CVN_NCScore", estimate=3_000_000)
        cos_sig = get_np_from_tree(sig_reco_tree, "DiffCosAngleTotalMom", estimate=3_000_000)

        # grids
        if index0 < 4:
            cos_right_grid = np.array([0.9], dtype=np.float64)
            cos_left_grid = np.array([-0.9], dtype=np.float64)
            bdt_cuts = np.linspace(-0.2, 0.5, 50, dtype=np.float64)
            cvn_cuts = None
        else:
            if 3 < index0 < 8:
                cos_right_grid = np.linspace(0.85, 1.00, 10, dtype=np.float64)
                cos_left_grid = np.array([-1.1], dtype=np.float64)
                cvn_cuts = np.array([0.9], dtype=np.float64)
            else:
                cos_right_grid = np.linspace(0.8, 1.00, 20, dtype=np.float64)
                cos_left_grid = np.array([-1.1], dtype=np.float64)
                cvn_cuts = np.linspace(0.2, 0.5, 50, dtype=np.float64)
            bdt_cuts = None

        sig_name_from_file = Path(sig_reco_tree.GetCurrentFile().GetName()).stem
        f_info.write(f"Sample: {sig_name_from_file}\n")
        f_info.write(f"Number of Boosted DM Events Simulated: {simu_entries[sig_idx]}\n")
        f_info.write(f"Number of Boosted DM Events Reconstructed: {reco_entries[sig_idx]}\n")
        f_info.write(
            f"Ratio of Boosted DM Events Reconstructed: {float(reco_entries[sig_idx]) / float(simu_entries[sig_idx])}\n\n"
        )

        f_results.write(f"Sample: {sig_name_from_file}\n")

        best = None
        best_sprime = np.inf

        if index0 < 4:
            bdt_sig_all = get_bdt_response(sig_reco_tree, args.weights_xml)

            f_results.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tBDTCut\n")
            for bdt_cut in bdt_cuts:
                res = scan_best_cuts_bdt_only(
                    bdt_cut=float(bdt_cut),
                    cos_right_grid=cos_right_grid,
                    cos_left_grid=cos_left_grid,
                    n_signal_simulated=int(simu_entries[sig_idx]),
                    bdt_signal=bdt_sig_all,
                    bdt_atm=bdt_atm_all,
                    cos_signal=cos_sig,
                    cos_atm=cos_atm,
                    background_scale=background_scale,
                )
                if res[0] < best_sprime:
                    best_sprime = float(res[0])
                    best = res

        else:
            f_results.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tCVNCut\n")
            for cvn_cut in cvn_cuts:
                res = scan_best_cuts_cvn_only(
                    cvn_cut=float(cvn_cut),
                    cos_right_grid=cos_right_grid,
                    cos_left_grid=cos_left_grid,
                    n_signal_simulated=int(simu_entries[sig_idx]),
                    cvn_signal=cvn_sig,
                    cvn_atm=cvn_atm,
                    cos_signal=cos_sig,
                    cos_atm=cos_atm,
                    background_scale=background_scale,
                )
                if res[0] < best_sprime:
                    best_sprime = float(res[0])
                    best = res

        if best is None:
            print(f"[WARN] No valid cut point found for sample {sig_name_from_file}")
            f_results.write("\n")
            continue

        if index0 < 4:
            f_results.write(
                f"BDT_ONLY\t{best[0]}\t{best[1]}\t{best[2]}\t{best[3]}\t{best[4]}\t{best[5]}\t{best[6]}\n"
            )
            f_effbkg.write(
                f"BDT_ONLY\t{best[0]}\t{best[1]}\t{best[2]}\t{best[3]}\t{best[4]}\t{best[5]}\t{best[6]}\n"
            )
            cos_sig_after = best[7]
            cos_atm_after = best[8]
            # arrays -> .npy
            save_npy(get_bdt_response(sig_reco_tree, args.weights_xml), outdir / f"BDT_{out_tag}_ALL.npy")
        else:
            f_results.write(
                f"CVN_ONLY\t{best[0]}\t{best[1]}\t{best[2]}\t{best[3]}\t{best[4]}\t{best[5]}\t{best[6]}\n"
            )
            f_effbkg.write(
                f"CVN_ONLY\t{best[0]}\t{best[1]}\t{best[2]}\t{best[3]}\t{best[4]}\t{best[5]}\t{best[6]}\n"
            )
            cos_sig_after = best[7]
            cos_atm_after = best[8]

        # Save per-sample arrays -> .npy
        save_npy(np.asarray(cos_sig_after, dtype=np.float64), outdir / f"CosSunSignalAfterCuts_{out_tag}.npy")
        save_npy(np.asarray(cos_atm_after, dtype=np.float64), outdir / f"CosSunAtmAfterCuts_{out_tag}.npy")
        save_npy(cvn_sig, outdir / f"CVN_{out_tag}.npy")
        save_npy(cos_sig, outdir / f"CosSun_{out_tag}.npy")

        print("\n")
        print(index0)
        if index0 < 4:
            print("################# BEST BDT+ANG CUTS INFO #######################")
            print(f"Optimal Signal Strength: {best[0]:.0f}")
            print(f"Optimal BDT Cut: {best[6]:.3f}")
        else:
            print("################# BEST CVN+ANG CUTS INFO #######################")
            print(f"Optimal Signal Strength: {best[0]:.0f}")
            print(f"Optimal CVN Cut: {best[6]:.3f}")

        print(f"Optimal Positive Cosine Angular Cut: {best[2]:.3f}")
        print(f"Optimal Negative Cosine Angular Cut: {best[1]:.3f}")
        print(f"Signal Efficiency: {best[3]:.3f}")
        print(f"Number of expected Atm Nu events: {best[4]:.1f}, statistical uncertainty: {best[5]:.1f}")
        print("\n")

    f_info.close()
    f_results.close()
    f_effbkg.close()


if __name__ == "__main__":
    ROOT.gErrorIgnoreLevel = ROOT.kWarning
    main()
