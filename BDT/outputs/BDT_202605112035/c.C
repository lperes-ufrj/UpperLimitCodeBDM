#ifdef __CLING__
#pragma cling optimize(0)
#endif
void c()
{
//=========Macro generated from canvas: c/the canvas
//=========  (Mon Jun  8 11:09:36 2026) by ROOT version 6.30/08
   TCanvas *c = new TCanvas("c", "the canvas",200,69,650,500);
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
   
   TH2F *frame__33 = new TH2F("frame__33","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__33->SetStats(0);
   frame__33->SetLineWidth(2);
   frame__33->SetMarkerStyle(21);
   frame__33->SetMarkerSize(0.3);
   frame__33->GetXaxis()->SetTitle("Signal efficiency");
   frame__33->GetXaxis()->SetLabelOffset(0.012);
   frame__33->GetXaxis()->SetLabelSize(0.04);
   frame__33->GetXaxis()->SetTitleSize(0.045);
   frame__33->GetXaxis()->SetTitleOffset(1.25);
   frame__33->GetYaxis()->SetTitle("Background rejection");
   frame__33->GetYaxis()->SetLabelOffset(0.012);
   frame__33->GetYaxis()->SetLabelSize(0.04);
   frame__33->GetYaxis()->SetTitleSize(0.045);
   frame__33->GetYaxis()->SetTitleOffset(1.22);
   frame__33->GetZaxis()->SetLabelSize(0.04);
   frame__33->GetZaxis()->SetTitleSize(0.04);
   frame__33->GetZaxis()->SetTitleOffset(1);
   frame__33->Draw("");
   
   TH1D *MVA_BDTAtmCCNC_202605112035_rejBvsS__34 = new TH1D("MVA_BDTAtmCCNC_202605112035_rejBvsS__34","MVA_BDTAtmCCNC_202605112035",100,0,1);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(1,1);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(2,1);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(3,0.9998307);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(4,0.999746);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(5,0.9995767);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(6,0.9993227);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(7,0.999238);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(8,0.9988993);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(9,0.9986453);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(10,0.9985204);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(11,0.9980527);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(12,0.9978833);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(13,0.9973753);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(14,0.9966133);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(15,0.9960207);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(16,0.995428);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(17,0.9947104);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(18,0.993904);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(19,0.993396);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(20,0.992888);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(21,0.9922107);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(22,0.9907713);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(23,0.9900093);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(24,0.9887393);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(25,0.9877134);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(26,0.985776);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(27,0.9846753);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(28,0.9834053);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(29,0.9811807);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(30,0.9785793);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(31,0.9756339);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(32,0.9738919);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(33,0.9716419);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(34,0.9685039);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(35,0.9655406);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(36,0.9625497);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(37,0.959489);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(38,0.9546503);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(39,0.9511472);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(40,0.9465752);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(41,0.9426502);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(42,0.9387012);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(43,0.933944);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(44,0.9295127);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(45,0.9267632);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(46,0.9216692);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(47,0.9170844);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(48,0.9125339);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(49,0.9072813);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(50,0.9009218);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(51,0.8956963);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(52,0.8884811);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(53,0.8811278);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(54,0.8761875);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(55,0.8694339);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(56,0.862379);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(57,0.8547696);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(58,0.8484199);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(59,0.8392777);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(60,0.833037);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(61,0.8276705);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(62,0.8200734);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(63,0.8126852);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(64,0.8025541);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(65,0.7933466);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(66,0.7855886);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(67,0.7769029);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(68,0.7677483);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(69,0.7594227);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(70,0.7511367);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(71,0.7419625);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(72,0.7312675);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(73,0.7199433);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(74,0.704172);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(75,0.6947538);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(76,0.6856913);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(77,0.6774839);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(78,0.6661551);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(79,0.6510599);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(80,0.6407904);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(81,0.6289021);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(82,0.6158803);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(83,0.6029337);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(84,0.5893912);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(85,0.5729659);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(86,0.561938);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(87,0.5420403);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(88,0.5249132);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(89,0.5026028);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(90,0.4844277);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(91,0.4630465);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(92,0.4441093);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(93,0.4247894);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(94,0.3986919);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(95,0.3555859);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(96,0.3281708);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(97,0.2964027);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(98,0.2574824);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(99,0.2067098);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetBinContent(100,0.1085556);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetEntries(100);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->SetLineWidth(3);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202605112035_rejBvsS__34->Draw("csame");
   
   TH2F *frame__35 = new TH2F("frame__35","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__35->SetStats(0);
   frame__35->SetLineWidth(2);
   frame__35->SetMarkerStyle(21);
   frame__35->SetMarkerSize(0.3);
   frame__35->GetXaxis()->SetTitle("Signal efficiency");
   frame__35->GetXaxis()->SetLabelOffset(0.012);
   frame__35->GetXaxis()->SetLabelSize(0.04);
   frame__35->GetXaxis()->SetTitleSize(0.045);
   frame__35->GetXaxis()->SetTitleOffset(1.25);
   frame__35->GetYaxis()->SetTitle("Background rejection");
   frame__35->GetYaxis()->SetLabelOffset(0.012);
   frame__35->GetYaxis()->SetLabelSize(0.04);
   frame__35->GetYaxis()->SetTitleSize(0.045);
   frame__35->GetYaxis()->SetTitleOffset(1.22);
   frame__35->GetZaxis()->SetLabelSize(0.04);
   frame__35->GetZaxis()->SetTitleSize(0.04);
   frame__35->GetZaxis()->SetTitleOffset(1);
   frame__35->Draw("sameaxis");
   
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
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202605112035_rejBvsS","BDTAtmCCNC_202605112035","l");
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
   TPad *imgpad__18 = new TPad("imgpad", "imgpad",0.788395,0.91,0.95,0.965);
   imgpad__18->Draw();
   imgpad__18->cd();
   imgpad__18->Range(0,0,1,1);
   imgpad__18->SetFillColor(0);
   imgpad__18->SetBorderMode(0);
   imgpad__18->SetBorderSize(2);
   imgpad__18->SetTickx(1);
   imgpad__18->SetTicky(1);
   imgpad__18->SetLeftMargin(0);
   imgpad__18->SetRightMargin(0);
   imgpad__18->SetTopMargin(0);
   imgpad__18->SetBottomMargin(0);

   ci = TColor::GetColor("#fffffd");
   imgpad__18->SetFrameFillColor(ci);
   imgpad__18->SetFrameBorderMode(0);
   imgpad__18->SetFrameLineColor(0);
   imgpad__18->SetFrameBorderMode(0);

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
   imgpad__18->Modified();
   c->cd();
   c->Modified();
   c->SetSelected(c);
}
