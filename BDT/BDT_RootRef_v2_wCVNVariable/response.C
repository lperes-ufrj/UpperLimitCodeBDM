#ifdef __CLING__
#pragma cling optimize(0)
#endif
void response()
{
//=========Macro generated from canvas: canvas1/TMVA comparison BDTAtmCCNC_202503120817
//=========  (Wed Mar 12 08:45:37 2025) by ROOT version 6.32.00
   TCanvas *canvas1 = new TCanvas("canvas1", "TMVA comparison BDTAtmCCNC_202503120817",200,69,600,468);
   gStyle->SetOptStat(0);
   canvas1->Range(-0.9839011,-0.3108713,0.8809749,2.279723);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f0f0f0");
   canvas1->SetFillColor(ci);
   canvas1->SetBorderMode(0);
   canvas1->SetBorderSize(2);
   canvas1->SetTickx(1);
   canvas1->SetTicky(1);
   canvas1->SetRightMargin(0.05);
   canvas1->SetBottomMargin(0.12);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);
   
   TH2F *frameBDTAtmCCNC_202503120817__33 = new TH2F("frameBDTAtmCCNC_202503120817__33","TMVA overtraining check for classifier: BDTAtmCCNC_202503120817",500,-0.7880892,0.7877311,500,0,2.020664);
   frameBDTAtmCCNC_202503120817__33->SetStats(0);
   frameBDTAtmCCNC_202503120817__33->SetLineWidth(2);
   frameBDTAtmCCNC_202503120817__33->SetMarkerStyle(21);
   frameBDTAtmCCNC_202503120817__33->SetMarkerSize(0.3);
   frameBDTAtmCCNC_202503120817__33->GetXaxis()->SetTitle("BDTAtmCCNC_202503120817 response");
   frameBDTAtmCCNC_202503120817__33->GetXaxis()->SetLabelOffset(0.012);
   frameBDTAtmCCNC_202503120817__33->GetXaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__33->GetXaxis()->SetTitleSize(0.045);
   frameBDTAtmCCNC_202503120817__33->GetXaxis()->SetTitleOffset(1.25);
   frameBDTAtmCCNC_202503120817__33->GetYaxis()->SetTitle("(1/N) dN^{ }/^{ }dx");
   frameBDTAtmCCNC_202503120817__33->GetYaxis()->SetLabelOffset(0.012);
   frameBDTAtmCCNC_202503120817__33->GetYaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__33->GetYaxis()->SetTitleSize(0.045);
   frameBDTAtmCCNC_202503120817__33->GetYaxis()->SetTitleOffset(1.2);
   frameBDTAtmCCNC_202503120817__33->GetZaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__33->GetZaxis()->SetTitleSize(0.04);
   frameBDTAtmCCNC_202503120817__33->GetZaxis()->SetTitleOffset(1);
   frameBDTAtmCCNC_202503120817__33->Draw("");
   
   TLegend *leg = new TLegend(0.105,0.78,0.505,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);

   ci = TColor::GetColor("#7d8b9d");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1);
   TLegendEntry *entry=leg->AddEntry("MVA_BDTAtmCCNC_202503120817_S","Signal (test sample)","F");
   entry->SetFillColor(38);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#0000ee");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202503120817_B","Background (test sample)","F");
   entry->SetFillColor(2);
   entry->SetFillStyle(3554);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   TH1D *MVA_BDTAtmCCNC_202503120817_S__34 = new TH1D("MVA_BDTAtmCCNC_202503120817_S__34","TMVA overtraining check for classifier: BDTAtmCCNC_202503120817",40,-0.7880892,0.787731);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(4,0.00179847);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(5,0.00359694);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(6,0.00359694);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(7,0.007193881);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(8,0.02158164);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(9,0.03057399);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(10,0.02697705);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(11,0.03417093);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(12,0.06654339);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(13,0.1133036);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(14,0.15287);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(15,0.1960332);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(16,0.3057399);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(17,0.4352298);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(18,0.6294645);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(19,0.8668626);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(20,1.233751);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(21,1.420791);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(22,1.526901);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(23,1.485536);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(24,1.519707);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(25,1.37583);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(26,1.100664);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(27,1.068291);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(28,1.050307);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(29,1.095268);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(30,1.152819);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(31,1.323674);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(32,1.487335);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(33,1.454962);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(34,1.393814);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(35,0.9136228);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(36,1.091671);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(37,0.6384569);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(38,0.08812504);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(39,0.05755104);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinContent(40,0.008992351);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(4,0.00179847);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(5,0.002543421);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(6,0.002543421);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(7,0.00359694);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(8,0.006230083);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(9,0.007415282);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(10,0.006965445);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(11,0.00783935);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(12,0.01093967);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(13,0.01427491);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(14,0.01658108);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(15,0.01877658);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(16,0.02344918);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(17,0.02797763);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(18,0.0336463);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(19,0.03948451);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(20,0.04710481);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(21,0.05054949);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(22,0.05240311);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(23,0.05168842);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(24,0.05227952);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(25,0.04974323);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(26,0.04449169);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(27,0.04383252);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(28,0.04346199);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(29,0.04438251);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(30,0.04553363);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(31,0.04879127);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(32,0.0517197);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(33,0.05115375);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(34,0.05006729);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(35,0.04053546);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(36,0.04430957);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(37,0.03388577);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(38,0.01258929);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(39,0.01017368);
   MVA_BDTAtmCCNC_202503120817_S__34->SetBinError(40,0.004021501);
   MVA_BDTAtmCCNC_202503120817_S__34->SetEntries(14114);
   MVA_BDTAtmCCNC_202503120817_S__34->SetFillColor(38);

   ci = TColor::GetColor("#0000ee");
   MVA_BDTAtmCCNC_202503120817_S__34->SetLineColor(ci);
   MVA_BDTAtmCCNC_202503120817_S__34->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_S__34->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_S__34->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_S__34->Draw("samehist");
   
   TH1D *MVA_BDTAtmCCNC_202503120817_B__35 = new TH1D("MVA_BDTAtmCCNC_202503120817_B__35","MVA_BDTAtmCCNC_202503120817_B",40,-0.7880892,0.787731);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(1,0.003927831);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(2,0.069719);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(3,0.2690564);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(4,0.5557881);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(5,1.043821);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(6,1.352156);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(7,1.205844);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(8,1.097829);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(9,1.100775);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(10,1.076226);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(11,1.122378);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(12,1.19897);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(13,1.247086);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(14,1.390452);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(15,1.402236);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(16,1.360993);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(17,1.428749);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(18,1.451334);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(19,1.393398);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(20,1.378669);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(21,1.215664);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(22,0.9505351);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(23,0.6775508);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(24,0.5135639);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(25,0.3211002);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(26,0.1796983);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(27,0.1070334);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(28,0.06873704);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(29,0.05204376);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(30,0.03731439);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(31,0.03633244);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(32,0.03535048);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(33,0.01669328);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(34,0.01276545);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(35,0.002945873);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinContent(36,0.006873704);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(1,0.001963915);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(2,0.008274123);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(3,0.01625429);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(4,0.02336152);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(5,0.03201544);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(6,0.03643844);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(7,0.03441058);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(8,0.03283324);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(9,0.03287726);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(10,0.03250859);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(11,0.0331983);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(12,0.03431236);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(13,0.03499409);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(14,0.03695085);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(15,0.03710709);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(16,0.03655733);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(17,0.03745625);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(18,0.03775113);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(19,0.03698997);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(20,0.03679394);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(21,0.0345504);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(22,0.03055135);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(23,0.02579392);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(24,0.02245658);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(25,0.01775688);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(26,0.01328368);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(27,0.01025194);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(28,0.008215648);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(29,0.00714876);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(30,0.006053194);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(31,0.005973016);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(32,0.005891746);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(33,0.004048715);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(34,0.003540499);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(35,0.001700801);
   MVA_BDTAtmCCNC_202503120817_B__35->SetBinError(36,0.002598016);
   MVA_BDTAtmCCNC_202503120817_B__35->SetEntries(25850);
   MVA_BDTAtmCCNC_202503120817_B__35->SetFillColor(2);
   MVA_BDTAtmCCNC_202503120817_B__35->SetFillStyle(3554);
   MVA_BDTAtmCCNC_202503120817_B__35->SetLineColor(2);
   MVA_BDTAtmCCNC_202503120817_B__35->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_B__35->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_B__35->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_B__35->Draw("samehist");
   
   leg = new TLegend(0.53,0.78,0.95,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);

   ci = TColor::GetColor("#7d8b9d");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1);
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202503120817_Train_S","Signal (training sample)","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ee");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(62);
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202503120817_Train_B","Background (training sample)","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry->SetTextFont(62);
   leg->Draw();
   
   TH1D *MVA_BDTAtmCCNC_202503120817_Train_S__36 = new TH1D("MVA_BDTAtmCCNC_202503120817_Train_S__36","MVA_BDTAtmCCNC_202503120817_Train_S",40,-0.7880892,0.787731);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(0,3.47723e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(2,6.954461e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(3,0.0001043169);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(4,0.0008345353);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(5,0.003338141);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(6,0.006884916);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(7,0.009597156);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(8,0.01491732);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(9,0.02048089);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(10,0.03199052);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(11,0.04370879);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(12,0.05939109);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(13,0.09103389);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(14,0.1404801);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(15,0.2077297);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(16,0.2908355);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(17,0.4355231);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(18,0.6416533);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(19,0.8732021);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(20,1.188413);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(21,1.444546);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(22,1.549906);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(23,1.554357);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(24,1.552479);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(25,1.404314);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(26,1.123667);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(27,0.9844039);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(28,1.103395);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(29,1.109097);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(30,1.143939);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(31,1.282646);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(32,1.460506);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(33,1.476919);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(34,1.414815);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(35,0.9153461);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(36,1.042891);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(37,0.6028474);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(38,0.08978209);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(39,0.06248583);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(40,0.005076756);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinContent(41,0.0001390892);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(0,3.47723e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(2,4.917546e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(3,6.02274e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(4,0.0001703488);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(5,0.0003406976);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(6,0.0004892897);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(7,0.0005776809);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(8,0.0007202149);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(9,0.0008439002);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(10,0.001054696);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(11,0.001232824);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(12,0.001437068);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(13,0.001779173);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(14,0.002210162);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(15,0.002687609);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(16,0.003180098);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(17,0.003891547);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(18,0.004723533);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(19,0.005510286);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(20,0.006428363);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(21,0.007087326);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(22,0.007341239);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(23,0.007351773);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(24,0.007347331);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(25,0.006987935);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(26,0.006250799);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(27,0.00585064);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(28,0.006194157);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(29,0.006210143);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(30,0.006306933);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(31,0.006678365);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(32,0.007126371);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(33,0.007166301);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(34,0.007014014);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(35,0.005641692);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(36,0.006021936);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(37,0.004578471);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(38,0.001766898);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(39,0.001474034);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(40,0.0004201553);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetBinError(41,6.954461e-05);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetEntries(730000);

   ci = TColor::GetColor("#0000ee");
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetLineColor(ci);

   ci = TColor::GetColor("#0000ee");
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetMarkerColor(ci);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetMarkerStyle(20);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->SetMarkerSize(0.7);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_S__36->Draw("e1same");
   
   TH1D *MVA_BDTAtmCCNC_202503120817_Train_B__37 = new TH1D("MVA_BDTAtmCCNC_202503120817_Train_B__37","MVA_BDTAtmCCNC_202503120817_Train_B",40,-0.7880892,0.787731);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(0,0.00013538);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(1,0.006588491);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(2,0.07179651);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(3,0.2286793);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(4,0.558668);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(5,1.043024);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(6,1.289359);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(7,1.216017);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(8,1.118633);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(9,1.124579);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(10,1.13454);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(11,1.104227);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(12,1.156833);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(13,1.262294);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(14,1.382816);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(15,1.381349);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(16,1.369391);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(17,1.42651);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(18,1.439168);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(19,1.439089);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(20,1.424175);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(21,1.233943);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(22,0.9530749);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(23,0.6877189);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(24,0.486251);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(25,0.3019763);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(26,0.1667091);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(27,0.1038139);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(28,0.08223205);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(29,0.05552835);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(30,0.03789511);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(31,0.0325476);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(32,0.02496632);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(33,0.0169789);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(34,0.01189087);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(35,0.005460325);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(36,0.003440907);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(37,0.001173293);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(38,0.0002143516);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinContent(39,5.640832e-05);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(0,3.908083e-05);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(1,0.0002726337);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(2,0.0008999911);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(3,0.001606201);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(4,0.002510519);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(5,0.003430312);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(6,0.003813936);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(7,0.003703875);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(8,0.00355247);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(9,0.003561898);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(10,0.003577639);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(11,0.00352952);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(12,0.003612617);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(13,0.003773695);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(14,0.003949742);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(15,0.003947647);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(16,0.003930522);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(17,0.004011659);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(18,0.004029418);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(19,0.004029307);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(20,0.004008374);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(21,0.003731077);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(22,0.003279066);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(23,0.002785429);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(24,0.002342161);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(25,0.00184575);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(26,0.001371407);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(27,0.001082217);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(28,0.0009631792);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(29,0.0007914873);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(30,0.00065385);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(31,0.0006059629);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(32,0.000530718);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(33,0.0004376646);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(34,0.0003662633);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(35,0.0002481966);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(36,0.0001970258);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(37,0.0001150508);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(38,4.917563e-05);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetBinError(39,2.522657e-05);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetEntries(2250000);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetLineColor(2);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetMarkerColor(2);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetMarkerStyle(20);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->SetMarkerSize(0.7);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_Train_B__37->Draw("e1same");
   TText *text = new TText(0.12,0.74,"Kolmogorov-Smirnov test: signal (background) probability = 0.647 (0.657)");
   text->SetNDC();
   text->SetTextSize(0.032);
   text->Draw();
   
   TH2F *frameBDTAtmCCNC_202503120817__38 = new TH2F("frameBDTAtmCCNC_202503120817__38","TMVA overtraining check for classifier: BDTAtmCCNC_202503120817",500,-0.7880892,0.7877311,500,0,2.020664);
   frameBDTAtmCCNC_202503120817__38->SetStats(0);
   frameBDTAtmCCNC_202503120817__38->SetLineWidth(2);
   frameBDTAtmCCNC_202503120817__38->SetMarkerStyle(21);
   frameBDTAtmCCNC_202503120817__38->SetMarkerSize(0.3);
   frameBDTAtmCCNC_202503120817__38->GetXaxis()->SetTitle("BDTAtmCCNC_202503120817 response");
   frameBDTAtmCCNC_202503120817__38->GetXaxis()->SetLabelOffset(0.012);
   frameBDTAtmCCNC_202503120817__38->GetXaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__38->GetXaxis()->SetTitleSize(0.045);
   frameBDTAtmCCNC_202503120817__38->GetXaxis()->SetTitleOffset(1.25);
   frameBDTAtmCCNC_202503120817__38->GetYaxis()->SetTitle("(1/N) dN^{ }/^{ }dx");
   frameBDTAtmCCNC_202503120817__38->GetYaxis()->SetLabelOffset(0.012);
   frameBDTAtmCCNC_202503120817__38->GetYaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__38->GetYaxis()->SetTitleSize(0.045);
   frameBDTAtmCCNC_202503120817__38->GetYaxis()->SetTitleOffset(1.2);
   frameBDTAtmCCNC_202503120817__38->GetZaxis()->SetLabelSize(0.04);
   frameBDTAtmCCNC_202503120817__38->GetZaxis()->SetTitleSize(0.04);
   frameBDTAtmCCNC_202503120817__38->GetZaxis()->SetTitleOffset(1);
   frameBDTAtmCCNC_202503120817__38->Draw("sameaxis");
   text = new TText(0.975,0.115,"U/O-flow (S,B): (0.0, 0.0)% / (0.0, 0.0)%");
   text->SetNDC();
   text->SetTextSize(0.03);
   text->SetTextAngle(90);
   text->Draw();
   
   TPaveText *pt = new TPaveText(0.01,0.9355405,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);

   ci = TColor::GetColor("#5d6b7d");
   pt->SetFillColor(ci);

   ci = TColor::GetColor("#7d8b9d");
   pt->SetLineColor(ci);
   pt->SetTextColor(0);
   TText *pt_LaTex = pt->AddText("TMVA overtraining check for classifier: BDTAtmCCNC_202503120817");
   pt->Draw();
  
// ------------>Primitives in pad: imgpad
   TPad *imgpad__12 = new TPad("imgpad", "imgpad",0.7866555,0.91,0.95,0.96819);
   imgpad__12->Draw();
   imgpad__12->cd();
   imgpad__12->Range(0,0,1,1);
   imgpad__12->SetFillColor(0);
   imgpad__12->SetBorderMode(0);
   imgpad__12->SetBorderSize(2);
   imgpad__12->SetTickx(1);
   imgpad__12->SetTicky(1);
   imgpad__12->SetLeftMargin(0);
   imgpad__12->SetRightMargin(0);
   imgpad__12->SetTopMargin(0);
   imgpad__12->SetBottomMargin(0);

   ci = TColor::GetColor("#fffffd");
   imgpad__12->SetFrameFillColor(ci);
   imgpad__12->SetFrameBorderMode(0);
   imgpad__12->SetFrameLineColor(0);
   imgpad__12->SetFrameBorderMode(0);

/* XPM */
const char *xpm_tmva_logo_gif_1[] = {
/* columns rows colors chars-per-pixel */
"98 26 92 2",
"   c #6A517C",
" . c #73587C",
" X c #FF0303",
" o c #FF1805",
" O c #FF1F1F",
" + c #FF330B",
" @ c #FF2D2D",
" # c #FF3333",
" $ c #FF410D",
" % c #FF5310",
" & c #FF7016",
" * c #815F70",
" = c #9C6E5D",
" - c #AD7B51",
" ; c #B07851",
" : c #866370",
" > c #FF4F4F",
" , c #FF5353",
" < c #FF6666",
" 1 c #FF7272",
" 2 c #34349B",
" 3 c #3535A0",
" 4 c #403B9A",
" 5 c #3F40A5",
" 6 c #4A428F",
" 7 c #53478E",
" 8 c #41419F",
" 9 c #624D81",
" 0 c #685482",
" q c #625497",
" w c #4E4EAC",
" e c #5858AF",
" r c #5C5CB0",
" t c #625FB1",
" y c #6262B4",
" u c #7979BF",
" i c #7C7CC3",
" p c #826B8D",
" a c #D8913F",
" s c #F59F2C",
" d c #E39533",
" f c #FFAC28",
" g c #FFAE30",
" h c #FFB43D",
" j c #BE814C",
" k c #B48B7F",
" l c #C88746",
" z c #D89140",
" x c #FFB643",
" c c #FFBE5F",
" v c #FFA873",
" b c #F2BC6D",
" n c #FFC158",
" m c #FFC76A",
" M c #FFCB7F",
" N c #9C869B",
" B c #B99285",
" V c #8383BF",
" C c #FF8686",
" Z c #FF9696",
" A c #D8B498",
" S c #EFBD8B",
" D c #FFBF8B",
" F c #FFA0A0",
" G c #FFB8B8",
" H c #8181C3",
" J c #9C9CCC",
" K c #9F9FD2",
" L c #A8A8D6",
" P c #B9B9DF",
" I c #BEBEE2",
" U c #FFCC80",
" Y c #FFD389",
" T c #FFD691",
" R c #EDC9A0",
" E c #FFDFAC",
" W c #FFE2AD",
" Q c #FFE6B8",
" ! c #FFC6C6",
" ~ c #FFD8D8",
" ^ c #CECEE5",
" / c #D2D2EC",
" ( c #D9D9F1",
" ) c #FFECC8",
" _ c #FFEED8",
" ` c #FFF0D0",
" ' c #FFECEC",
" ] c #E7E7F2",
" [ c #F5EEF8",
" { c #FFF5E2",
" } c #FFFFFF",
" | c None",
" } } } } } } } } } } } } } } } } } ` c f f h M { } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } } } Y f f f f f f f { } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } } Q f f f f f f f f x } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } } x f f f f f f f f f T } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } { f f f f f f f f f f h } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } W f f f f f f f f f f f { } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }",
" } } } } } } } } } } } } } } W f f f f f f f f f f f ` } } } } } } } } } } } } ! X X X X X X X X X X O y 2 2 3 ] } } } } K 2 2 3 J } H 2 2 w } } } } } P 3 2 r } } } } ] 2 2 3 w } } } } } } } } } }",
" } } } } } } } } } } } } } } Q f f f f f f f f f f f } } } } } } } } } } } } } Z X X X X X X X X X X > y 2 2 3 H } } } } w 2 3 2 K } I 2 2 3 ^ } } } } u 3 2 L } } } } L 2 2 3 2 ] } } } } } } } } }",
" } } } } } } } } } } } } } } { f f f f f f f f f f x } } } } } } } } } } } } } F < < < @ X X O < < < G t 2 2 2 5 [ } } ^ 2 2 3 2 K } } 3 2 2 K } } } ] 2 2 3 } } } } } e 3 2 2 2 L } } } } } } } } }",
" } } } } } } } } } } } } } } } m f f f f f f f f f ) } } } } } } } } } } } } } } } } } > X X 1 } } } } y 2 2 3 2 J } } u 3 2 2 2 K } } H 2 2 e } } } L 2 2 u } } } } / 2 3 2 3 2 e } } } } } } } } }",
" } } } } } } } } } } } } } } } { g f f f f f f f m } } } } } } } } } } } } } } } } } } @ X X F } } } } y 2 2 3 2 w } ] 2 2 w 2 2 K } } ^ 2 2 3 ] } } u 3 2 L } } } } K 2 2 K 2 2 3 ] } } } } } } } }",
" } } } } } } } } } } } } } } } } m h f f f f f x Q } } } } } } } } } } } } } } } } } ' X X X ~ } } } } y 2 2 i 2 2 ( V 3 e y 2 2 K } } } w 2 3 P } } w 2 2 ] } } } } e 3 2 ] u 2 2 H } } } } } } } }",
" } } } } } } } } } { ) ` } } } T W { U n g m E } Y ` } } } ) ) { } } } } } } } } } } G X X X } } } } } y 2 2 ^ 2 2 i 2 2 K y 2 2 K } } } H 2 2 i } / 2 3 e } } } } ] 2 2 w } P 3 2 w } } } } } } } }",
" } } } } } } } { ) { } } ) ` { T } } } } } } } } } n _ ) ` } } { ) } } } } } } } } } C X X # } } } } } y 2 2 ( V 3 2 2 2 ] y 2 2 K } } } I 2 2 w } K 2 2 J } } } } L 2 2 i } } 3 2 2 ( } } } } } } }",
" } } } } } } { { } } } } } } T } } } } } } } } } } { E } } } } } } ` { } } } } } } } , X X < } } } } } y 2 2 ( / 2 2 3 e } y 2 2 K } } } } 3 2 2 ^ y 2 2 ^ } } } } e 2 3 J ^ / e 2 3 J } } } } } } }",
" } } } } } { { } } } } } } } } { } } } } } } } } } ) } } } } } } } } ` } } } } } } } @ X X Z } } } } } y 2 2 ( } y 2 2 L } y 2 2 K } } } } u 3 2 u 2 3 8 } } } } ( 2 2 2 3 2 2 2 3 2 r } } } } } } }",
" E T T T T E } } } } } } } } } ) T T T T T T T T Y } } } } } } } } } } T T T T T T D X X X v T T T T T q 2 2 A T k 0   S T q 2 2 N T T T T B 2 2 3 2 2 p T T T T N 3 2 2 2 3 2 2 2 3 2 R T T T T T E",
" x f f f f ` } } } } } } } } } { f f f f f f f f M } } } } } } } } } } M f f f f f & X X X f f f f f f 9 2 2 a f f f f f f   2 3 = f f f f f 8 2 2 2 3 d f f f f 9 2 2 : ; - ; - 6 3 2 ; f f f f f c",
" x f f f f } } } } } } } } } } } f f f f f f f f W } } } } } } } } } } W f f f f f $ X X + f f f f f f 9 2 2 z f f f f f f   2 3 = f f f f f * 2 2 2 7 f f f f d 2 2 4 f f f f f * 2 2 0 f f f f f c",
" x f f f f } } } } } } } } } } } f f f f f f f f W } } } } } } } } } } W f f f f f o X X % f f f f f f 9 2 2 a f f f f f f   2 3 = f f f f f l 2 2 3 = f f f f - 2 2 . f f f f f j 2 3 2 s f f f f n",
" x f f f f } } } } } } } } } } } f f f f f f f f Y } } } } } } } } } } Y f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f c",
" x f f f f Q } } } } } } } } } ) f f f f f f f f n } } } } } } } } } } n f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f c",
" x f f f f c } } } } } } } } } Y f f f f f f f f f { } } } } } } } } { f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f n",
" x f f f f f E } } } } } } } ` f f f f f f f f f f x } } } } } } } } m f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f c",
" x f f f f f f Q } } } } } ) h f f f f f f f f f f f c { } } } } { m f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f f c",
" b n c n c n c n U ) ) ) T c n c n c n c n c n c n c n m E ) ) Q M c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n c n U"
};


   TImage *xpm_tmva_logo_gif_1_img = TImage::Create();
   xpm_tmva_logo_gif_1_img->SetImageBuffer( (char **)xpm_tmva_logo_gif_1, TImage::kXpm);
   xpm_tmva_logo_gif_1_img->Draw();
   imgpad__12->Modified();
   canvas1->cd();
   canvas1->Modified();
   canvas1->SetSelected(canvas1);
}
