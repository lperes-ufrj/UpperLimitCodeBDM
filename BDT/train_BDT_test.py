import ROOT
import time

# Initialize TMVA
ROOT.TMVA.Tools.Instance()

# Define file path
path = '/home/leoperes/ntuples_grid_newVertex/00a_newVertex/'
root_file = path + 'atm_hA_BR.root'

# Open ROOT file with error checking
stree = ROOT.TFile.Open(root_file)
if not stree or stree.IsZombie():
    print(f"Error: Unable to open ROOT file at {root_file}")
    exit(1)

# Get tree
tree = stree.Get("ana/Atm")
if not tree:
    print("Error: Could not find tree 'ana/Atm' in file.")
    exit(1)

# Define signal and background cuts
sigCut = ROOT.TCut("CCNC == 1")  # Signal: Charged Current (CC)
bgCut = ROOT.TCut("CCNC == 0")   # Background: Neutral Current (NC)

# Print statistics
print(f"Total Signal Events: {tree.GetEntries(sigCut.GetTitle())}")
print(f"Total Background Events: {tree.GetEntries(bgCut.GetTitle())}")

# Define output file with timestamp
timestamp = time.strftime("%Y%m%d%H%M")
fout = ROOT.TFile(f"BDT_{timestamp}_Atm.root", "RECREATE")

# Define TMVA Factory
factory = ROOT.TMVA.Factory(
    "TMVAClassification", fout, 
    ":".join([
        "!V",               # Verbose off
        "!Silent",          # No batch mode silence
        "Color",            # Colored output
        "DrawProgressBar",  # Show training progress
        "Transformations=I;D;P;U;G,D",  # Input transformations
        "AnalysisType=Classification"
    ])
)

# Create DataLoader
dataloader = ROOT.TMVA.DataLoader("dataset")

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
        "nTrain_Signal=730000",
        "nTrain_Background=2250000",
        "SplitMode=Random",
        "NormMode=None",  
        "!V"
    ])
)

# Book BDT method with optimized parameters
method = factory.BookMethod(
    dataloader, ROOT.TMVA.Types.kBDT, f"BDTAtmCCNC_{timestamp}",
    ":".join([
    "!H", # Hide histograms in GUI
    "!V", # Disable verbosity
    "NTrees=200", # Number of trees
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

print("TMVA training and evaluation completed successfully!")
