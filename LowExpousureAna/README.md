# LowExpousureAna

Low-exposure copy of the main analysis chain for **100 kt-year**.

The main repository workflow is normalized to 400 kt-year, interpreted as:

```text
40 kton x 10 years = 400 kt-year
```

This folder uses:

```text
10 kton x 10 years = 100 kt-year
```

## What changed

- `Optimization_DefaultNuclearModel_final/Calc_OptCut_100kty.py`
  - Atmospheric background scale changed from `40 x ExpectedBkg10kty / n_sim_atm`
    to `10 x ExpectedBkg10kty / n_sim_atm`.

- `NuclearModelsOptSelectionApplication_final/ApplyNominalCuts_ToOtherNuclearModels_100kty.py`
  - Same 100 kt-year atmospheric background scale.
  - Keeps the same nominal-cut application logic as the main workflow.

- `CLs_final/CalcUpperLimit_wSyst_100kty.py`
  - Signal normalization changed from `NA_dune = 4 * 1.5e32` to
    `NA_dune = 1 * 1.5e32`, with `livetime_dune = 10 years`.
  - Adds `--path-eff`, `--seed`, `--sample-start`, `--sample-stop`, and
    `--poi-upper-scale`.
  - Applies the same positive-efficiency mask to `B_syst`, `NA_dune_syst`,
    and `eff_syst` to avoid array-length mismatches.

## Run Order

Run each script from its own directory so relative output paths stay local to
`LowExpousureAna`.

### 1. Optimize nominal cuts at 100 kt-year

```bash
cd LowExpousureAna/Optimization_DefaultNuclearModel_final

python3 Calc_OptCut_100kty.py \
  --base-path /home/leoperes \
  --sun-pos-file /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/Optimization/background_sun_pos.dat \
  --weights-xml /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/BDT/outputs/BDT_202605112035/dataset_202605112035/weights/TMVAClassification_202605112035_BDTAtmCCNC_202605112035.weights.xml \
  --seed 12345
```

This creates:

```text
LowExpousureAna/Optimization_DefaultNuclearModel_final/generated/<timestamp>/
```

### 2. Apply nominal cuts to all nuclear models

```bash
cd LowExpousureAna/NuclearModelsOptSelectionApplication_final

python3 ApplyNominalCuts_ToOtherNuclearModels_100kty.py \
  --base-path /home/leoperes \
  --sun-pos-file /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/Optimization/background_sun_pos.dat \
  --weights-xml /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/BDT/outputs/BDT_202605112035/dataset_202605112035/weights/TMVAClassification_202605112035_BDTAtmCCNC_202605112035.weights.xml \
  --nominal-eff-bkg ../Optimization_DefaultNuclearModel_final/generated/<timestamp>/Eff_Bkg_index_00a.txt \
  --seed 12345
```

This creates:

```text
LowExpousureAna/NuclearModelsOptSelectionApplication_final/generated/<timestamp>/
```

### 3. Calculate CLs limits at 100 kt-year

```bash
cd LowExpousureAna/CLs_final

python3 CalcUpperLimit_wSyst_100kty.py \
  --path-eff ../NuclearModelsOptSelectionApplication_final/generated/<timestamp> \
  --seed 12345
```

Useful subset run:

```bash
python3 CalcUpperLimit_wSyst_100kty.py \
  --path-eff ../NuclearModelsOptSelectionApplication_final/generated/<timestamp> \
  --sample-start 4 \
  --sample-stop 8 \
  --seed 12345
```

If a limit is not found because the scan range is too low, increase:

```bash
--poi-upper-scale 2.0
```

### 4. Plot 100 kt-year and 400 kt-year sensitivities together

```bash
cd LowExpousureAna/CLs_final

python3 PlotSensDUNE_LowExposure.py \
  --low-dir plots/<low_timestamp> \
  --high-dir /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/CLs/CLs_final/plots/<high_timestamp>
```

For the current completed runs:

```bash
python3 PlotSensDUNE_LowExposure.py \
  --low-dir plots/20260512_223056 \
  --high-dir /home/leoperes/Desktop/UpperLimitCodeBDMv4/UpperLimitCodeBDM/CLs/CLs_final/plots/20260512_101630
```

This writes one timestamped folder under:

```text
LowExpousureAna/CLs_final/plots/
```

and creates one plot per gamma, with timestamped filenames.
