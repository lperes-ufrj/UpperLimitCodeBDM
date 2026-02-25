#!/usr/bin/env python3
"""
ApplyNominalCuts_ToOtherNuclearModels.py

Apply the *nominal optimal cuts* (from a mode-aware Eff_Bkg_index file)
to other nuclear model configurations.

Rules (ENFORCED):
  GROUP A (index0 < 4):
    - Use ONLY (BDT cut + angular cuts).
    - Ignore CVN completely.
    - Compute BDT for ALL reco entries.

  GROUP B (index0 >= 4):
    - Use ONLY (CVN cut + angular cuts).
    - If CVN == -1, drop the event entirely.
    - Do NOT use BDT.

Output:
  ./generated/YYYYMMDD_HHMMSS/<model_name>/
    - Sensitivity_Info_<code>.txt
    - Sensitivity_results_<code>.txt
    - Eff_Bkg_index_<code>.txt
    - arrays saved as .npy (CVN, BDT, CosSun, etc.)

    python3 ApplyNominalCuts_ToOtherNuclearModels.py \
  --base-path /home/leoperes \
  --sun-pos-file ../background_sun_pos.dat \
  --weights-xml /home/leoperes/Desktop/UpperLimitCodeBDM_final/UpperLimitCodeBDM/BDT/dataset/weights/TMVAClassification_BDTAtmCCNC_202601261224.weights.xml \
  --nominal-eff-bkg /home/leoperes/Desktop/UpperLimitCodeBDM_final/UpperLimitCodeBDM/Optimization/Optimization_DefaultNuclearModel_final/generated/20260216_172956/Eff_Bkg_index_00a.txt \
  --seed 12345



"""

from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Tuple, Optional

import argparse
import math
import numpy as np

import ROOT
from array import array


# -----------------------------
# Constants / sample ordering
# -----------------------------
SAMPLES_12 = [
    "m05_b1p1", "m10_b1p1", "m20_b1p1", "m40_b1p1",
    "m05_b1p5", "m10_b1p5", "m20_b1p5", "m40_b1p5",
    "m05_b10",  "m10_b10",  "m20_b10",  "m40_b10",
]

DEFAULT_NUCLEAR_MODELS = [
    ("hA_BR", "00a"),
    ("hA_LFG", "01a"),
    ("hA_ESF", "02a"),
    ("hN_BR", "00b"),
    ("hN_LFG", "01b"),
    ("hN_ESF", "02b"),
]

MISSING_SAMPLE_BY_CODE = {
    "01a": {"m20_b10"},
}

ATM_FILE_FIXED = "atm_hA_BR_4ana.root"
EXPECTED_BKG_10KTY = 2495.98


# -----------------------------
# Utilities
# -----------------------------
def create_run_output_dir(base: str = "generated") -> Path:
    ts = datetime.now().strftime("%Y%m%d_%H%M%S")
    d = Path.cwd() / base / ts
    d.mkdir(parents=True, exist_ok=True)
    print("\n========================================")
    print(f" Saving outputs to:\n {d}")
    print("========================================\n")
    return d


def save_npy(arr: np.ndarray, filename: Path) -> None:
    """
    Save numpy arrays to .npy (binary, fast, preserves dtype/shape).
    """
    filename.parent.mkdir(parents=True, exist_ok=True)
    arr_np = np.asarray(arr)
    if filename.suffix != ".npy":
        filename = filename.with_suffix(".npy")
    np.save(str(filename), arr_np)


def write_header(fh, header: str) -> None:
    fh.write(header + "\n\n")


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


# -----------------------------
# TMVA BDT response (ALL events)
# -----------------------------
def get_bdt_response_all(tree: ROOT.TTree, weights_xml: Path) -> np.ndarray:
    """
    Compute TMVA BDT response for ALL reco entries in the tree.
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

    nentry = int(tree.GetEntries())
    out = np.empty(nentry, dtype=np.float64)

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

        out[i] = float(reader.EvaluateMVA("TMVAClassification"))

    return out


# -----------------------------
# Sun positions helper (cache)
# -----------------------------
def load_sun_positions(sun_pos_file: Path) -> np.ndarray:
    sun_pos_file = Path(sun_pos_file)
    if not sun_pos_file.exists():
        raise FileNotFoundError(f"Sun position file not found: {sun_pos_file}")

    sun_positions = np.loadtxt(str(sun_pos_file), delimiter="\t", usecols=(0, 1, 2))
    if sun_positions.ndim != 2 or sun_positions.shape[1] != 3:
        raise RuntimeError(f"Sun positions must be Nx3. Got shape={sun_positions.shape}")
    return sun_positions.astype(np.float64, copy=False)


# -----------------------------
# Atmospheric cos(theta_sun,reco)
# -----------------------------
def build_cos_sun_from_mom_unitvec(
    reco_tree: ROOT.TTree,
    sun_positions: np.ndarray,
    rng: np.random.Generator,
) -> Tuple[np.ndarray, int]:
    """
    Uses branch " TotalMomRecoRangeUnitVect" (leading space!) which is N*3.
    Returns cos_sun array (len N) and N.
    """
    mom = get_np_from_tree_raw(reco_tree, " TotalMomRecoRangeUnitVect", estimate=300_000_000)
    n_reco = int(reco_tree.GetEntries())
    if mom.size != 3 * n_reco:
        raise RuntimeError(
            f"Unexpected size for TotalMomRecoRangeUnitVect: got {mom.size}, expected {3*n_reco}"
        )

    reco_mom = np.reshape(mom, (n_reco, 3))
    idx = rng.integers(0, len(sun_positions), size=n_reco)
    sun = sun_positions[idx]

    cos = np.einsum("ij,ij->i", reco_mom, sun).astype(np.float64)
    return cos, n_reco


# -----------------------------
# Cuts application (fixed cuts)
# -----------------------------
def apply_fixed_bdt_and_angle(
    *,
    bdt_cut: float,
    cos_left: float,
    cos_right: float,
    bdt_scores: np.ndarray,
    cos_values: np.ndarray,
) -> Tuple[np.ndarray, int]:
    """
    Select events:
      - bdt > bdt_cut
      - AND (cos > cos_right OR cos < cos_left)
    Returns:
      selected_cos, n_selected
    """
    if bdt_scores.shape[0] != cos_values.shape[0]:
        raise RuntimeError(f"BDT and cos arrays have different lengths: {bdt_scores.shape[0]} vs {cos_values.shape[0]}")

    mask_bdt = bdt_scores > bdt_cut
    cos_sel = cos_values[mask_bdt]
    mask_ang = (cos_sel > cos_right) | (cos_sel < cos_left)
    selected = cos_sel[mask_ang]
    return selected, int(selected.size)


def apply_fixed_cvn_and_angle_drop_minus1(
    *,
    cvn_cut: float,
    cos_left: float,
    cos_right: float,
    cvn_scores: np.ndarray,
    cos_values: np.ndarray,
) -> Tuple[np.ndarray, int]:
    """
    Drop CVN==-1 entirely, then:
      - cvn > cvn_cut
      - AND (cos > cos_right OR cos < cos_left)
    """
    if cvn_scores.shape[0] != cos_values.shape[0]:
        raise RuntimeError(f"CVN and cos arrays have different lengths: {cvn_scores.shape[0]} vs {cos_values.shape[0]}")

    valid = cvn_scores > -1
    cvn_v = cvn_scores[valid]
    cos_v = cos_values[valid]

    mask_cvn = cvn_v > cvn_cut
    cos_sel = cos_v[mask_cvn]
    mask_ang = (cos_sel > cos_right) | (cos_sel < cos_left)
    selected = cos_sel[mask_ang]
    return selected, int(selected.size)


# -----------------------------
# Nominal cut file parsing
# -----------------------------
@dataclass(frozen=True)
class NominalCuts:
    mode: str          # "BDT_ONLY" or "CVN_ONLY"
    sprime: float
    cos_left: float
    cos_right: float
    eff: float
    bkg: float
    bkg_err: float
    cut_value: float   # BDTCut if mode=BDT_ONLY, CVNCut if mode=CVN_ONLY


def load_nominal_cuts(nominal_eff_bkg_file: Path) -> Dict[str, NominalCuts]:
    """
    Reads the mode-aware Eff_Bkg_index file:

      Mode   SigStrength  NegCosCut  PosCosCut  bestEff  BkgExpect  BkgError  CutValue

    Maps row i -> SAMPLES_12[i].
    """
    nominal_eff_bkg_file = Path(nominal_eff_bkg_file)
    if not nominal_eff_bkg_file.exists():
        raise FileNotFoundError(f"Nominal Eff_Bkg file not found: {nominal_eff_bkg_file}")

    lines = nominal_eff_bkg_file.read_text().splitlines()

    rows: List[NominalCuts] = []
    for ln in lines:
        ln = ln.strip()
        if not ln:
            continue
        if ln.lower().startswith("mode"):
            continue

        parts = ln.split("\t")
        if len(parts) == 1:
            parts = ln.split()

        if len(parts) < 8:
            continue

        mode = parts[0].strip()
        try:
            sprime = float(parts[1])
            cos_left = float(parts[2])
            cos_right = float(parts[3])
            eff = float(parts[4])
            bkg = float(parts[5])
            bkg_err = float(parts[6])
            cut_value = float(parts[7])
        except ValueError:
            continue

        rows.append(
            NominalCuts(
                mode=mode,
                sprime=sprime,
                cos_left=cos_left,
                cos_right=cos_right,
                eff=eff,
                bkg=bkg,
                bkg_err=bkg_err,
                cut_value=cut_value,
            )
        )

    if len(rows) < len(SAMPLES_12):
        raise RuntimeError(
            f"Nominal cuts file has {len(rows)} data rows, expected {len(SAMPLES_12)}.\n"
            f"Make sure it contains exactly one row per sample in the nominal ordering."
        )

    out: Dict[str, NominalCuts] = {}
    for i, tag in enumerate(SAMPLES_12):
        out[tag] = rows[i]

    return out


# -----------------------------
# ROOT file opening per nuclear model
# -----------------------------
def open_model_files(
    base_path: Path,
    model_name: str,
    model_code: str,
    subdir_template: str
) -> List[Tuple[str, ROOT.TFile]]:
    """
    Returns list of (tag, TFile):
      first is atmosphere: ("atm", file)
      then samples (subset of SAMPLES_12 depending on missing).
    """
    base_path = Path(base_path)
    subdir = base_path / subdir_template.format(code=model_code)
    if not subdir.exists():
        raise FileNotFoundError(f"Subdir not found: {subdir}")

    # Atmosphere fixed file (00a) as per your original workflow
    atm_path = (base_path / "ntuples_grid_newVertex/00a_newVertex" / ATM_FILE_FIXED)
    if not atm_path.exists():
        raise FileNotFoundError(f"Atmosphere file not found: {atm_path}")
    atm_f = ROOT.TFile.Open(str(atm_path))
    if not atm_f or atm_f.IsZombie():
        raise RuntimeError(f"Failed to open atmosphere file: {atm_path}")

    out: List[Tuple[str, ROOT.TFile]] = [("atm", atm_f)]

    missing = MISSING_SAMPLE_BY_CODE.get(model_code, set())

    for tag in SAMPLES_12:
        if tag in missing:
            continue
        fname = f"bdm_{tag}_{model_code}.root"
        fpath = subdir / fname
        if not fpath.exists():
            raise FileNotFoundError(f"Missing signal ROOT file for model {model_name}/{model_code}: {fpath}")
        tf = ROOT.TFile.Open(str(fpath))
        if not tf or tf.IsZombie():
            raise RuntimeError(f"Failed to open ROOT file: {fpath}")
        out.append((tag, tf))

    return out


def get_tree(tf: ROOT.TFile, name: str) -> ROOT.TTree:
    t = tf.Get(name)
    if not t:
        raise KeyError(f"Tree '{name}' not found in file {tf.GetName()}")
    return t


# -----------------------------
# Main
# -----------------------------
def main() -> None:
    parser = argparse.ArgumentParser(
        description="Apply nominal optimal cuts to other nuclear model configurations (BDT-only for first 4, CVN-only for the rest)."
    )
    parser.add_argument("--base-path", required=True, type=Path, help="Base path containing ntuples_grid_newVertex/...")
    parser.add_argument(
        "--subdir-template",
        default="ntuples_grid_newVertex/{code}_newVertex",
        help="Template for nuclear-model subdir under base-path. Use {code} placeholder.",
    )
    parser.add_argument("--sun-pos-file", required=True, type=Path, help="Path to background_sun_pos.dat")
    parser.add_argument("--weights-xml", required=True, type=Path, help="TMVA weights XML (needed for BDT-only group)")
    parser.add_argument("--nominal-eff-bkg", required=True, type=Path, help="Nominal Eff_Bkg_index file (Eff_Bkg_index_00a.txt)")
    parser.add_argument("--seed", default=12345, type=int, help="RNG seed for sun-position sampling.")
    parser.add_argument("--append", action="store_true", help="Append to output files (default: overwrite).")
    args = parser.parse_args()

    outdir = create_run_output_dir()
    rng = np.random.default_rng(args.seed)

    sun_positions = load_sun_positions(args.sun_pos_file)
    nominal_cuts = load_nominal_cuts(args.nominal_eff_bkg)

    for model_name, model_code in DEFAULT_NUCLEAR_MODELS:
        model_out = outdir / model_name
        model_out.mkdir(parents=True, exist_ok=True)

        file_list = open_model_files(
            base_path=args.base_path,
            model_name=model_name,
            model_code=model_code,
            subdir_template=args.subdir_template,
        )

        # ---------- Atmosphere ----------
        _, atm_file = file_list[0]
        atm_reco = get_tree(atm_file, "ana/Atm")
        atm_simu = get_tree(atm_file, "ana/AllEvents")

        cos_atm, n_reco_atm = build_cos_sun_from_mom_unitvec(atm_reco, sun_positions, rng)
        n_sim_atm = int(atm_simu.GetEntries())
        ratio_reco_atm = n_reco_atm / float(n_sim_atm)

        cvn_atm = get_np_from_tree(atm_reco, "CVN_NCScore")

        # Compute once (used only for index0<4; okay to compute anyway)
        bdt_atm_all = get_bdt_response_all(atm_reco, args.weights_xml)

        background_scale = 4.0 * 10.0 * ratio_reco_atm * EXPECTED_BKG_10KTY / float(n_sim_atm)

        # ---------- Output files ----------
        mode = "a" if args.append else "w"
        f_info = open(model_out / f"Sensitivity_Info_{model_code}.txt", mode)
        f_results = open(model_out / f"Sensitivity_results_{model_code}.txt", mode)
        f_eff = open(model_out / f"Eff_Bkg_index_{model_code}.txt", mode)

        write_header(f_info, "################# SAMPLE INFO #######################")
        f_info.write(f"MODEL: {model_name}  CODE: {model_code}\n")
        f_info.write(f"Atmos Simulated: {n_sim_atm}\n")
        f_info.write(f"Atmos Reco: {n_reco_atm}\n")
        f_info.write(f"Reco/Sim ratio: {ratio_reco_atm}\n\n")

        if not args.append:
            f_eff.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tCutValue\n")

        # ---------- Save atmosphere arrays as NPY ----------
        save_npy(cvn_atm, model_out / f"CVN_Atm_{model_code}.npy")
        save_npy(bdt_atm_all, model_out / f"BDT_Atm_{model_code}_ALL.npy")
        save_npy(cos_atm, model_out / f"CosSun_Atm_{model_code}.npy")

        # ---------- Apply cuts per signal sample ----------
        for tag, tf in file_list[1:]:
            reco_tree = get_tree(tf, "ana/Atm")
            simu_tree = get_tree(tf, "ana/AllEvents")

            n_sig_sim = int(simu_tree.GetEntries())
            n_sig_reco = int(reco_tree.GetEntries())

            cvn_sig = get_np_from_tree(reco_tree, "CVN_NCScore")
            cos_sig = get_np_from_tree(reco_tree, "DiffCosAngleTotalMom")

            # Consistency sanity: arrays must match reco entries
            if cvn_sig.shape[0] != n_sig_reco or cos_sig.shape[0] != n_sig_reco:
                raise RuntimeError(
                    f"[{model_name}/{model_code}] {tag}: array length mismatch "
                    f"(reco={n_sig_reco}, cvn={cvn_sig.shape[0]}, cos={cos_sig.shape[0]})"
                )

            cuts = nominal_cuts[tag]
            cos_left = cuts.cos_left
            cos_right = cuts.cos_right

            index0 = SAMPLES_12.index(tag)

            # ENFORCE rule by index0 (not by what nominal file says)
            if index0 < 4:
                mode_name = "BDT_ONLY"
                bdt_cut = cuts.cut_value

                # BDT computed for all reco entries
                bdt_sig_all = get_bdt_response_all(reco_tree, args.weights_xml)

                cos_sig_after, n_sig_sel = apply_fixed_bdt_and_angle(
                    bdt_cut=bdt_cut,
                    cos_left=cos_left,
                    cos_right=cos_right,
                    bdt_scores=bdt_sig_all,
                    cos_values=cos_sig,
                )

                cos_atm_after, n_bkg_sel = apply_fixed_bdt_and_angle(
                    bdt_cut=bdt_cut,
                    cos_left=cos_left,
                    cos_right=cos_right,
                    bdt_scores=bdt_atm_all,
                    cos_values=cos_atm,
                )

                cut_value = bdt_cut

            else:
                mode_name = "CVN_ONLY"
                cvn_cut = cuts.cut_value

                cos_sig_after, n_sig_sel = apply_fixed_cvn_and_angle_drop_minus1(
                    cvn_cut=cvn_cut,
                    cos_left=cos_left,
                    cos_right=cos_right,
                    cvn_scores=cvn_sig,
                    cos_values=cos_sig,
                )

                cos_atm_after, n_bkg_sel = apply_fixed_cvn_and_angle_drop_minus1(
                    cvn_cut=cvn_cut,
                    cos_left=cos_left,
                    cos_right=cos_right,
                    cvn_scores=cvn_atm,
                    cos_values=cos_atm,
                )

                cut_value = cvn_cut

            # Efficiency and expected bkg
            eff = float(n_sig_sel) / float(n_sig_sim) if n_sig_sim > 0 else 0.0
            bkg_expect = float(n_bkg_sel) * background_scale
            bkg_err = float(math.sqrt(max(n_bkg_sel, 0.0) * background_scale))

            # S'
            if eff > 0:
                sprime = 25.0 / (2.0 * eff) + math.sqrt(
                    25.0 * bkg_expect / (eff * eff) + 625.0 / (4.0 * eff * eff)
                )
            else:
                sprime = float("inf")

            # ---------- Write info/results ----------
            f_info.write(f"Sample: {tag} (index0={index0})\n")
            f_info.write(f"Signal Sim: {n_sig_sim}\n")
            f_info.write(f"Signal Reco: {n_sig_reco}\n")
            f_info.write(f"Reco/Sim: {n_sig_reco/float(n_sig_sim) if n_sig_sim>0 else 0.0}\n\n")

            f_results.write(f"Sample: {tag}\n")
            if mode_name == "BDT_ONLY":
                f_results.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tBDTCut\n")
            else:
                f_results.write("Mode\tSigStrength\tNegCosCut\tPosCosCut\tbestEff\tBkgExpect\tBkgError\tCVNCut\n")

            f_results.write(
                f"{mode_name}\t{sprime}\t{cos_left}\t{cos_right}\t{eff}\t{bkg_expect}\t{bkg_err}\t{cut_value}\n\n"
            )

            f_eff.write(
                f"{mode_name}\t{sprime}\t{cos_left}\t{cos_right}\t{eff}\t{bkg_expect}\t{bkg_err}\t{cut_value}\n"
            )

            # ---------- Save arrays as NPY ----------
            save_npy(cos_sig_after, model_out / f"CosSunSignalAfterCuts_{tag}_{model_code}.npy")
            save_npy(cos_atm_after, model_out / f"CosSunAtmAfterCuts_{tag}_{model_code}.npy")
            save_npy(cvn_sig, model_out / f"CVN_{tag}_{model_code}.npy")
            save_npy(cos_sig, model_out / f"CosSun_{tag}_{model_code}.npy")

            if index0 < 4:
                save_npy(bdt_sig_all, model_out / f"BDT_{tag}_{model_code}_ALL.npy")

            print("\n")
            print(f"[{model_name}/{model_code}] {tag}")
            print(f"  Mode: {mode_name}")
            print(f"  S'    : {sprime:.3f}")
            print(f"  cosL  : {cos_left:.3f}")
            print(f"  cosR  : {cos_right:.3f}")
            print(f"  cut   : {cut_value:.3f}")
            print(f"  eff   : {eff:.5f}")
            print(f"  bkg   : {bkg_expect:.3f} +/- {bkg_err:.3f}")

        f_info.close()
        f_results.close()
        f_eff.close()


if __name__ == "__main__":
    ROOT.gErrorIgnoreLevel = ROOT.kWarning
    main()
