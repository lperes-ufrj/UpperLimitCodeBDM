**UpperLimitCodeBDM**

Tools and analysis scripts for Boosted Dark Matter Analysis in DUNE. The repository contains training Boosted Decision Trees (BDT), optimizing selections, validating performance, and CLs upper limits scripts. 
**Repository Structure**
- **BDT**: BDT training scripts, notebooks, ROOT macros, and datasets. See [BDT](BDT) for training and plotting utilities.
- **CLs**: Scripts and inputs for CLs-based upper limit calculations and sensitivity plots. See [CLs](CLs).
- **Optimization**: Notebooks and utilities for cut/selection optimization. See [Optimization](Optimization).
- **ValidationStudies**: Evaluation notebooks, comparison plots, and systematic studies. See [ValidationStudies](ValidationStudies).

**Quick Start**
- Requirements: Python 3.8+ and common scientific packages. Typical install (adjust to your environment):

```
python -m pip install numpy pandas matplotlib scikit-learn jupyter notebook uproot
```

- Usage workflow (recommended order):

	1. Find the optimal selection for the nominal nuclear model with the optimization script. Example:

	```bash
	python Optimization/Optimization_DefaultNuclearModel_final/Calc_OptCut.py
	```

	This script scans selection cuts and determines the optimal cut(s) for the nominal model; it writes the recommended cut values (Eff_Bkg_index_00a.txt) that will be used in the next step.

	2. Apply the nominal selection to other nuclear models using the application script. Example:

	```bash
	python Optimization/NuclearModelsOptSelectionApplication_final/ApplyNominalCuts_ToOtherNuclearModels.py
	```

	This step reads the nominal cut values and applies them to the alternative nuclear-model datasets, producing selected samples or summary outputs for each model.

	3. Calculate the sensitivity / CLs upper limits using the prepared inputs. Example:

	```bash
	python CLs/CLs_final/CalcUpperLimit_wSyst.py
	```

	Update `CLs/parameters.ini` (or the script arguments) to point to the prepared input files produced by step 2. The `CLs` scripts will read those inputs and produce the final sensitivity and limit plots/tables.


**Data samples**
- The samples used for development and testing are available here: https://drive.google.com/drive/folders/1FTyRupcFJqptV6i8D_OlXe7QxSHgji9K?usp=sharing
- After downloading, place the files into the expected locations (for example `BDT/dataset/`) or update paths as described in **Reproducibility & Paths**.

**Key files & notebooks**
- BDT training and utilities: [BDT/train_BDT.py](BDT/train_BDT.py), [BDT/train_BDT_final_ref.py](BDT/train_BDT_final_ref.py), notebooks in [BDT](BDT).
- CLs calculation examples: [CLs/CalcUpperLimit_wSyst.py](CLs/CalcUpperLimit_wSyst.py), [CLs/parameters.ini](CLs/parameters.ini).
- Validation & plotting notebooks: see [ValidationStudies](ValidationStudies).

**Legacy & Final Folders**
- **Final / *_final**: Folders or files with `final` in their name (for example `CLs_final` or the `BDT_v2_woCVNVariable` directory) contain production-ready or preferred configurations and outputs used for the main analyses and reported results. Prefer these when reproducing the primary results.
- **Legacy / old_***: Directories prefixed with `old_` or kept for historical reference (for example `BDT/old_BDT_v1`) are archived experiments, earlier model versions, and legacy TMVA outputs. They are useful for provenance and comparisons but are not recommended for new analyses.

**Reproducibility & Paths**
- Reproducing the analyses exactly may require reorganizing dataset and output paths (for example `BDT/dataset/`, `BDT/weights/`, `BDT/plots/`, and input CSVs under `CLs/`). Many scripts use relative or hard-coded locations and read paths from `CLs/parameters.ini` or BDT scripts — update those paths or move files into the expected layout before running. I can prepare a helper script or a suggested directory layout if you want.

**License & Contact**
- Repository: https://github.com/lperes-ufrj/UpperLimitCodeBDM
- Open issues or contact the repository owner for questions.
-

