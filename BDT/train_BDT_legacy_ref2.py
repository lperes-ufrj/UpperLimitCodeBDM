import ROOT
import time

# in order to start TMVA
ROOT.TMVA.Tools.Instance()

# open file
path = '/media/leoperes/Acer/Users/le0_p/ntuples_grid_newVertex/00a_newVertex/'
stree = ROOT.TFile.Open(path+'atm_hA_BR.root')

# get trees 
tree_s = stree.Get("ana/Atm")
tree_b = stree.Get("ana/Atm")

fout = ROOT.TFile("BDT_"+str(time.strftime("%Y%m%d%H%M"))+"Atm.root","RECREATE")

# define factory with options
factory = ROOT.TMVA.Factory("TMVAClassification", fout, #TMVA::Factory( "<JobName>", outputFile, "<options>" );
                            ":".join([    "!V", # Verbose flag, default=False
                                          "!Silent", # Batch mode: boolean silent flag inhibiting any output from TMVA after the creation of the factory class object (default: False)
                                          "Color", # Flag for coloured screen output (default: True, if in batch mode: False)
                                          "DrawProgressBar", # Draw progress bar to display training, testing and evaluation schedule (default: True)
                                          "Transformations=I;D;P;U;G,D", # List of transformations to test; formatting example: Transformations=I;D;P;U;G,D, for identity, decorrelation, PCA, Uniform and Gaussianisation followed by decorrelation transformations
                                          "AnalysisType=Classification"] # Set the analysis type (Classification, Regression, Multiclass, Auto) (default: Auto)
                                     ))

dataloader = ROOT.TMVA.DataLoader("dataset")

dataloader.AddSpectator("event", "I")
# add discriminating variables for training
#dataloader.AddVariable("LongestTrack","F") # Longest Track in the event [cm]
#dataloader.AddVariable("log(HighestTrackSummedADC)/log(HighestShowerSummedADC)","F") # Highest Track ADC deposition in the events [ADC Units]
dataloader.AddVariable("PIDALongestTrack", "F") # PIDA of the longest track
dataloader.AddVariable("nTracks", "I") # number of tracks in the event
dataloader.AddVariable("nShowers", "I") # number of showers in the event
#dataloader.AddVariable("TotalMomentumP", "F") # total momentum magnitude of the event with only tracks info
dataloader.AddVariable("NHits", "I") # number of 3d space points reco
#dataloader.AddVariable("NPrimaryDaughters", "I") # nShowers+nTracks in the event (irrelevant, it can be take off)
dataloader.AddVariable("log(HighestShowerSummedADC)", "F") # Highest Shower ADC deposition in the events [ADC Units]
#dataloader.AddVariable("PrimaryPDGReco", "I") # Pandora returns for nue or numu
dataloader.AddVariable("LargeShowerOpenAngle", "F") # Large shower open Angle [rad]
dataloader.AddVariable("LongestShower", "F") # Longest Shower in the event [cm]
#dataloader.AddVariable("CosThetaDetTotalMom", "F") # Total momentum Cossine Theta detector coordinates.
#dataloader.AddVariable("CosPhiDetTotalMom", "F") # Total momentum Cossine Phi detector coordinates.
#dataloader.AddVariable("FracTotalChargeLongTrack", "F") # How much of the total charge of the event the longest track carries
#dataloader.AddVariable("AvarageTrackLength", "F") # Avarage track length in the event [cm]
dataloader.AddVariable("CVN_NCScore", "F") # CVN score for NC
#dataloader.AddVariable("EventRecoEnergy_Charge", "F") # Event Energy given the charge deposition in the event.
#dataloader.AddVariable("nSpacePoints","F")
# define signal and background trees
dataloader.AddSignalTree(tree_s)
dataloader.AddBackgroundTree(tree_b)

# define additional cuts 
sigCut = ROOT.TCut("CCNC == 1")
bgCut = ROOT.TCut("CCNC == 0")

# set options for trainings
dataloader.PrepareTrainingAndTestTree(sigCut, 
                                   bgCut, 
                                   ":".join(["nTrain_Signal=730000",
                                             "nTrain_Background=2250000",
                                             "SplitMode=Random",
                                             "NormMode=NumEvents",
                                             "!V"
                                             ]))

method = factory.BookMethod(dataloader, ROOT.TMVA.Types.kBDT, "BDTAtmCCNC_"+str(time.strftime("%Y%m%d%H%M")),
                            ":".join([ "!H",
                                       "!V",
                                       "NTrees=450",
                                       "MinNodeSize=5%",
                                       "MaxDepth=4",
                                       "BoostType=AdaBoost",
                                       "AdaBoostBeta=0.5",
                                       "SeparationType=GiniIndex",
                                       "nCuts=20",
                                       "PruneMethod=NoPruning",
                                       "DoBoostMonitor=True"
                                       ]))

# self-explaining
factory.TrainAllMethods()
factory.TestAllMethods()
factory.EvaluateAllMethods()