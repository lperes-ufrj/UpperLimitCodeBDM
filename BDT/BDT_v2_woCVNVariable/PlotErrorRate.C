void PlotBDTErrorRate() {
    // Open the TMVA output file
    TFile *file = TFile::Open("BDT_202503120817_Atm.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open TMVA.root" << std::endl;
        return;
    }

    // Navigate to the BDT method directory
    TDirectory *dir = (TDirectory*)file->Get("dataset/Method_BDT/BDTAtmCCNC_202503120817/");
    if (!dir) {
        std::cerr << "Error: Could not find Method_BDT/BDT in TMVA.root" << std::endl;
        return;
    }

    // Retrieve the error graphs from training and testing
    TGraph *gTrainROC = (TGraph*)dir->Get("MVA_BDTAtmCCNC_202503120817_trainingRejBvsS");
    TGraph *gTestROC = (TGraph*)dir->Get("MVA_BDTAtmCCNC_202503120817_rejBvsS");

    if (!gTrainROC || !gTestROC) {
        std::cerr << "Error: Could not find ROC curves in TMVA output!" << std::endl;
        return;
    }

    // Convert rejection (1 - Background Efficiency) to error rate
    Int_t n = gTrainROC->GetN();
    std::vector<double> x(n), trainError(n), testError(n);

    for (int i = 0; i < n; i++) {
        double sigEff, bgRej;
        gTrainROC->GetPoint(i, sigEff, bgRej);
        trainError[i] = 1.0 - bgRej;  // Error = 1 - Background Rejection

        gTestROC->GetPoint(i, sigEff, bgRej);
        testError[i] = 1.0 - bgRej;  // Error = 1 - Background Rejection

        x[i] = sigEff;  // Use signal efficiency as the x-axis
    }

    // Create graphs for training and testing error
    TGraph *gTrainError = new TGraph(n, x.data(), trainError.data());
    TGraph *gTestError = new TGraph(n, x.data(), testError.data());

    // Create a canvas
    TCanvas *c = new TCanvas("c", "BDT Error Rate Evolution", 800, 600);
    c->SetGrid();

    // Style settings
    gTrainError->SetTitle("BDT Training and Testing Error Evolution");
    gTrainError->GetXaxis()->SetTitle("Boosting Iterations");
    gTrainError->GetYaxis()->SetTitle("Error Rate");
    gTrainError->SetLineColor(kRed);
    gTrainError->SetLineWidth(2);
    gTestError->SetLineColor(kBlue);
    gTestError->SetLineWidth(2);

    // Draw graphs
    gTrainError->Draw("AL");
    gTestError->Draw("L SAME");

    // Add a legend
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.85);
    leg->AddEntry(gTrainError, "Training Error", "l");
    leg->AddEntry(gTestError, "Testing Error", "l");
    leg->Draw();

    // Save the plot
    c->SaveAs("BDT_ErrorRate.png");
}