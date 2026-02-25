#ifdef __CLING__
#pragma cling optimize(0)
#endif
void c()
{
//=========Macro generated from canvas: c/the canvas
//=========  (Mon Feb 23 10:37:39 2026) by ROOT version 6.30/08
   TCanvas *c = new TCanvas("c", "the canvas",200,37,650,500);
   gStyle->SetOptStat(0);
   c->Range(-0.128266,0.07692306,1.059382,1.102564);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f0f0f0");
   c->SetFillColor(ci);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetGridx();
   c->SetGridy();
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetRightMargin(0.05);
   c->SetBottomMargin(0.12);

   ci = TColor::GetColor("#fffffd");
   c->SetFrameFillColor(ci);
   c->SetFrameBorderMode(0);

   ci = TColor::GetColor("#fffffd");
   c->SetFrameFillColor(ci);
   c->SetFrameBorderMode(0);
   
   TH2F *frame__30 = new TH2F("frame__30","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__30->SetStats(0);
   frame__30->SetLineWidth(2);
   frame__30->SetMarkerStyle(21);
   frame__30->SetMarkerSize(0.3);
   frame__30->GetXaxis()->SetTitle("Signal efficiency");
   frame__30->GetXaxis()->SetLabelOffset(0.012);
   frame__30->GetXaxis()->SetLabelSize(0.04);
   frame__30->GetXaxis()->SetTitleSize(0.045);
   frame__30->GetXaxis()->SetTitleOffset(1.25);
   frame__30->GetYaxis()->SetTitle("Background rejection");
   frame__30->GetYaxis()->SetLabelOffset(0.012);
   frame__30->GetYaxis()->SetLabelSize(0.04);
   frame__30->GetYaxis()->SetTitleSize(0.045);
   frame__30->GetYaxis()->SetTitleOffset(1.22);
   frame__30->GetZaxis()->SetLabelSize(0.04);
   frame__30->GetZaxis()->SetTitleSize(0.04);
   frame__30->GetZaxis()->SetTitleOffset(1);
   frame__30->Draw("");
   
   TH1D *MVA_BDTAtmCCNC_202601261224_rejBvsS__31 = new TH1D("MVA_BDTAtmCCNC_202601261224_rejBvsS__31","MVA_BDTAtmCCNC_202601261224",100,0,1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(1,1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(2,1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(3,1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(4,0.9999613);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(5,0.9998066);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(6,0.9997292);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(7,0.9996905);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(8,0.9996132);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(9,0.9994197);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(10,0.9992263);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(11,0.9989168);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(12,0.9985687);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(13,0.9983752);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(14,0.9980658);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(15,0.9976402);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(16,0.9969826);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(17,0.9964797);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(18,0.9960542);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(19,0.9955899);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(20,0.9948162);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(21,0.9941586);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(22,0.9934812);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(23,0.992882);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(24,0.9920309);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(25,0.9911412);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(26,0.9899897);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(27,0.988472);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(28,0.9867653);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(29,0.9852611);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(30,0.9834043);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(31,0.9810832);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(32,0.9788429);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(33,0.9764207);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(34,0.9744681);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(35,0.9720569);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(36,0.9686756);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(37,0.9652641);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(38,0.9621567);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(39,0.9586503);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(40,0.9541944);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(41,0.9502128);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(42,0.9466968);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(43,0.9420938);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(44,0.9369079);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(45,0.9332019);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(46,0.9282361);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(47,0.9233265);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(48,0.9175155);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(49,0.9122474);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(50,0.9070627);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(51,0.9010723);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(52,0.8959106);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(53,0.8897044);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(54,0.883095);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(55,0.8769035);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(56,0.8708213);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(57,0.8641291);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(58,0.8574695);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(59,0.8514747);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(60,0.8441039);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(61,0.8370941);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(62,0.8303246);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(63,0.8230405);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(64,0.8156676);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(65,0.8080259);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(66,0.799729);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(67,0.7901683);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(68,0.7810653);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(69,0.7724143);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(70,0.7623197);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(71,0.7519656);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(72,0.7411021);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(73,0.7287966);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(74,0.7182286);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(75,0.7069279);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(76,0.6962408);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(77,0.6852646);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(78,0.6741582);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(79,0.6623092);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(80,0.6507285);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(81,0.6375439);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(82,0.6220526);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(83,0.6086021);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(84,0.5959234);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(85,0.5801814);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(86,0.5658041);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(87,0.5479971);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(88,0.5272655);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(89,0.5071907);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(90,0.4860908);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(91,0.4619598);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(92,0.4381366);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(93,0.4150416);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(94,0.3915319);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(95,0.3613626);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(96,0.3285257);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(97,0.2905594);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(98,0.2435861);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(99,0.1833969);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetBinContent(100,0.09274352);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetEntries(100);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->SetLineWidth(3);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202601261224_rejBvsS__31->Draw("csame");
   
   TH2F *frame__32 = new TH2F("frame__32","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__32->SetStats(0);
   frame__32->SetLineWidth(2);
   frame__32->SetMarkerStyle(21);
   frame__32->SetMarkerSize(0.3);
   frame__32->GetXaxis()->SetTitle("Signal efficiency");
   frame__32->GetXaxis()->SetLabelOffset(0.012);
   frame__32->GetXaxis()->SetLabelSize(0.04);
   frame__32->GetXaxis()->SetTitleSize(0.045);
   frame__32->GetXaxis()->SetTitleOffset(1.25);
   frame__32->GetYaxis()->SetTitle("Background rejection");
   frame__32->GetYaxis()->SetLabelOffset(0.012);
   frame__32->GetYaxis()->SetLabelSize(0.04);
   frame__32->GetYaxis()->SetTitleSize(0.045);
   frame__32->GetYaxis()->SetTitleOffset(1.22);
   frame__32->GetZaxis()->SetLabelSize(0.04);
   frame__32->GetZaxis()->SetTitleSize(0.04);
   frame__32->GetZaxis()->SetTitleOffset(1);
   frame__32->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0.15,0.171,0.5,0.281,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);

   ci = TColor::GetColor("#7d8b9d");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","MVA Method:","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202601261224_rejBvsS","BDTAtmCCNC_202601261224","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.01,0.9344958,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);

   ci = TColor::GetColor("#5d6b7d");
   pt->SetFillColor(ci);

   ci = TColor::GetColor("#7d8b9d");
   pt->SetLineColor(ci);
   pt->SetTextColor(0);
   TText *pt_LaTex = pt->AddText("Background rejection versus Signal efficiency");
   pt->Draw();
  
// ------------>Primitives in pad: imgpad
   TPad *imgpad__12 = new TPad("imgpad", "imgpad",0.788395,0.91,0.95,0.965);
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
"104 26 84 1",
"  c #6C547D",
". c #735778",
"X c #FF0505",
"o c #FF1D05",
"O c #FF1919",
"+ c #FF3209",
"@ c #FF2626",
"# c #FF3A3A",
"$ c #FF5C12",
"% c #FF6B15",
"& c #FF7B18",
"* c #9C6E5D",
"= c #AD7D53",
"- c #B07C55",
"; c #8F6768",
": c #936865",
"> c #9F7778",
", c #FF5643",
"< c #FF5353",
"1 c #FF6C6C",
"2 c #39389C",
"3 c #3636A0",
"4 c #463E91",
"5 c #5C4C88",
"6 c #494191",
"7 c #624D81",
"8 c #6C5181",
"9 c #6D5B96",
"0 c #4444A5",
"q c #5454A8",
"w c #5B5BB3",
"e c #736AA5",
"r c #6D6AB6",
"t c #7777BE",
"y c #7B7BC0",
"u c #FF941D",
"i c #DF9338",
"p c #F19E2E",
"a c #E79937",
"s c #FFA92D",
"d c #FFAE30",
"f c #FFB23D",
"g c #D28C40",
"h c #FFB949",
"j c #FFBF59",
"k c #F2BC6D",
"l c #FFC15F",
"z c #FFC063",
"x c #FFCA75",
"c c #FFD07F",
"v c #9C859B",
"b c #8383BF",
"n c #FF8F8F",
"m c #FF9999",
"M c #C4A08E",
"N c #ECBA85",
"B c #FFA8A8",
"V c #FFB9B9",
"C c #8F8FC9",
"Z c #9B9BCB",
"A c #9C9CD2",
"S c #A6A6D1",
"D c #B4B4DD",
"F c #BEBEE2",
"G c #FFCF89",
"H c #FFD389",
"J c #FFD690",
"K c #FFDEA4",
"L c #FFDEB6",
"P c #FFE1AC",
"I c #FFE6B8",
"U c #C1C1DF",
"Y c #FFCFCF",
"T c #FFDFDF",
"R c #C3C3E6",
"E c #DBDBEB",
"W c #DFDFF2",
"Q c #FFEFCE",
"! c #FFF0D0",
"~ c #FFECEC",
"^ c #ECECF8",
"/ c #FFF8E4",
"( c #FFFFFF",
") c None",
"((((((((((((((((((!zssslL(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((((Hsssssssx((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"((((((((((((((((IsssssssssJ(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"((((((((((((((((hssssssssss(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((!sssssssssssP((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((Jsssssssssssx((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((Jsssssssssssj((((((((((((((#XXXXXXXXXXOr223Z(((((t322A(Z232^(((((t32C(((((2322R((((((((((",
"(((((((((((((((KsssssssssssH((((((((((((((OXXXXXXXXXX#r223q((((^2232A(W223S(((((022W((((F2232Z((((((((((",
"(((((((((((((((/sssssssssssI(((((((((((((~1111XXX@111Br2232R(((C2232A((r22r((((D23q(((((y22230((((((((((",
"((((((((((((((((zsssssssssh((((((((((((((((((TXXXn((((r22320((^22322A((D322((((r22A(((((320223U(((((((((",
"((((((((((((((((/dssssssssI((((((((((((((((((VXXXY((((r22022D(C20223Z(((322D((^223R((((D32yq23b(((((((((",
"(((((((((((((((((zfssssssl(((((((((((((((((((nXXX(((((r22C23r^22y223Z(((t32t((S220(((((r22FS223(((((((((",
"((((((((((QQ/(((JP/GldlG/(x(((/QQ((((((((((((<XX#(((((r22At22y22R223Z(((S223((r22C((((^223^^223D((((((((",
"((((((((QQ((/Q/!J(((((((((Qx/Q/((!Q((((((((((@XX1(((((r22AR22230(322A(((^223D^223E((((S22w((r22r((((((((",
"(((((((Q((((((/H(((((((((((J!((((((!/(((((((~XXXm(((((r22A(0223Z(322A((((r22rD32q(((((q23bREC223^(((((((",
"((((((Q(((((((((/(((((((((//((((((((!(((((((BXXXY(((((r22A(S220((322A((((S223r22Z((((W2223222322D(((((((",
"KJJJJH((((((((((QJJJJJJJJJI((((((((((KJJJJJJ,XXXJJJJJJ922vJN 8>JJ223vJJJJN223222MJJJJv3222322232eJJJJJJK",
"hssssH((((((((((/sssssssssQ((((((((((KssssssoXX+ssssss 23*sssssss223*sssss.22326sssss722.-=-=.222ssssssj",
"hssssK(((((((((((sssssssss(((((((((((!sssssuXXX$ssssss 23*sssssss223*sssss=2232;ssssi223issssg222=sssssj",
"hssssK(((((((((((sssssssss(((((((((((!sssss%XXX&ssssss 23*sssssss223*sssssp3222assss:226ssssss4225sssssl",
"hssssK(((((((((((sssssssss!((((((((((Isssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssj",
"hssssz((((((((((QsssssssssI((((((((((Hsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssj",
"hsssss((((((((((Hsssssssssz((((((((((fsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssj",
"hsssssj((((((((QsssssssssssP((((((((xssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssl",
"hssssssh/(((((KsssssssssssssJ(((((/zsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssj",
"kljljljlzLQQQcjljljljljljljljGIQQIzjljljljljljljljljljljljljljljljljljljljljljljljljljljljljljljljljljlG"
};


   TImage *xpm_tmva_logo_gif_1_img = TImage::Create();
   xpm_tmva_logo_gif_1_img->SetImageBuffer( (char **)xpm_tmva_logo_gif_1, TImage::kXpm);
   xpm_tmva_logo_gif_1_img->Draw();
   imgpad__12->Modified();
   c->cd();
   c->Modified();
   c->SetSelected(c);
}
