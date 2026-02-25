#ifdef __CLING__
#pragma cling optimize(0)
#endif
void c()
{
//=========Macro generated from canvas: c/the canvas
//=========  (Wed Mar 12 08:45:56 2025) by ROOT version 6.32.00
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
   
   TH2F *frame__39 = new TH2F("frame__39","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__39->SetStats(0);
   frame__39->SetLineWidth(2);
   frame__39->SetMarkerStyle(21);
   frame__39->SetMarkerSize(0.3);
   frame__39->GetXaxis()->SetTitle("Signal efficiency");
   frame__39->GetXaxis()->SetLabelOffset(0.012);
   frame__39->GetXaxis()->SetLabelSize(0.04);
   frame__39->GetXaxis()->SetTitleSize(0.045);
   frame__39->GetXaxis()->SetTitleOffset(1.25);
   frame__39->GetYaxis()->SetTitle("Background rejection");
   frame__39->GetYaxis()->SetLabelOffset(0.012);
   frame__39->GetYaxis()->SetLabelSize(0.04);
   frame__39->GetYaxis()->SetTitleSize(0.045);
   frame__39->GetYaxis()->SetTitleOffset(1.22);
   frame__39->GetZaxis()->SetLabelSize(0.04);
   frame__39->GetZaxis()->SetTitleSize(0.04);
   frame__39->GetZaxis()->SetTitleOffset(1);
   frame__39->Draw("");
   
   TH1D *MVA_BDTAtmCCNC_202503120817_rejBvsS__40 = new TH1D("MVA_BDTAtmCCNC_202503120817_rejBvsS__40","MVA_BDTAtmCCNC_202503120817",100,0,1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(1,1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(2,1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(3,1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(4,1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(5,0.9999613);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(6,0.9998839);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(7,0.9998066);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(8,0.9997292);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(9,0.9997292);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(10,0.9996905);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(11,0.9996132);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(12,0.9995745);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(13,0.9994971);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(14,0.9994971);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(15,0.9993424);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(16,0.9992263);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(17,0.9991103);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(18,0.9989168);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(19,0.9988008);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(20,0.9986074);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(21,0.99853);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(22,0.9984913);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(23,0.9983752);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(24,0.9982205);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(25,0.9981044);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(26,0.9978337);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(27,0.9975242);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(28,0.9973745);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(29,0.9970097);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(30,0.9967892);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(31,0.9965571);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(32,0.9962476);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(33,0.9960155);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(34,0.9955899);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(35,0.9953578);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(36,0.995087);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(37,0.9945455);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(38,0.9942964);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(39,0.9940339);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(40,0.9936944);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(41,0.9929981);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(42,0.9925725);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(43,0.9920309);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(44,0.9914006);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(45,0.9909091);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(46,0.9904062);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(47,0.9891296);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(48,0.9883559);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(49,0.9873888);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(50,0.9861122);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(51,0.9851838);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(52,0.9837911);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(53,0.9819787);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(54,0.9803099);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(55,0.9786847);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(56,0.9768665);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(57,0.9743983);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(58,0.9728046);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(59,0.9696838);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(60,0.9671783);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(61,0.9646046);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(62,0.962089);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(63,0.9588733);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(64,0.9558183);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(65,0.9525452);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(66,0.9483403);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(67,0.944207);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(68,0.9406098);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(69,0.9359242);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(70,0.93199);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(71,0.9265392);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(72,0.9219631);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(73,0.9162656);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(74,0.9104489);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(75,0.9050317);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(76,0.8993397);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(77,0.8930337);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(78,0.8861509);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(79,0.8780215);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(80,0.8700379);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(81,0.861952);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(82,0.8539159);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(83,0.8461103);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(84,0.8355605);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(85,0.825403);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(86,0.8156002);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(87,0.8041524);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(88,0.7931335);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(89,0.7802534);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(90,0.7658266);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(91,0.7527783);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(92,0.7344081);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(93,0.7136925);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(94,0.6936418);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(95,0.6654681);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(96,0.6375679);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(97,0.6004244);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(98,0.5493153);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(99,0.4723124);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetBinContent(100,0.3458689);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetEntries(100);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->SetLineWidth(3);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetXaxis()->SetTitle("Signal eff");
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetXaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetXaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetXaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetYaxis()->SetTitle("Backgr rejection (1-eff)");
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetYaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetYaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetZaxis()->SetLabelFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetZaxis()->SetTitleOffset(1);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->GetZaxis()->SetTitleFont(42);
   MVA_BDTAtmCCNC_202503120817_rejBvsS__40->Draw("csame");
   
   TH2F *frame__41 = new TH2F("frame__41","Background rejection versus Signal efficiency",500,0,1,500,0.2,1);
   frame__41->SetStats(0);
   frame__41->SetLineWidth(2);
   frame__41->SetMarkerStyle(21);
   frame__41->SetMarkerSize(0.3);
   frame__41->GetXaxis()->SetTitle("Signal efficiency");
   frame__41->GetXaxis()->SetLabelOffset(0.012);
   frame__41->GetXaxis()->SetLabelSize(0.04);
   frame__41->GetXaxis()->SetTitleSize(0.045);
   frame__41->GetXaxis()->SetTitleOffset(1.25);
   frame__41->GetYaxis()->SetTitle("Background rejection");
   frame__41->GetYaxis()->SetLabelOffset(0.012);
   frame__41->GetYaxis()->SetLabelSize(0.04);
   frame__41->GetYaxis()->SetTitleSize(0.045);
   frame__41->GetYaxis()->SetTitleOffset(1.22);
   frame__41->GetZaxis()->SetLabelSize(0.04);
   frame__41->GetZaxis()->SetTitleSize(0.04);
   frame__41->GetZaxis()->SetTitleOffset(1);
   frame__41->Draw("sameaxis");
   
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
   entry=leg->AddEntry("MVA_BDTAtmCCNC_202503120817_rejBvsS","BDTAtmCCNC_202503120817","l");
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
   TPad *imgpad__13 = new TPad("imgpad", "imgpad",0.788395,0.91,0.95,0.965);
   imgpad__13->Draw();
   imgpad__13->cd();
   imgpad__13->Range(0,0,1,1);
   imgpad__13->SetFillColor(0);
   imgpad__13->SetBorderMode(0);
   imgpad__13->SetBorderSize(2);
   imgpad__13->SetTickx(1);
   imgpad__13->SetTicky(1);
   imgpad__13->SetLeftMargin(0);
   imgpad__13->SetRightMargin(0);
   imgpad__13->SetTopMargin(0);
   imgpad__13->SetBottomMargin(0);

   ci = TColor::GetColor("#fffffd");
   imgpad__13->SetFrameFillColor(ci);
   imgpad__13->SetFrameBorderMode(0);
   imgpad__13->SetFrameLineColor(0);
   imgpad__13->SetFrameBorderMode(0);

/* XPM */
const char *xpm_tmva_logo_gif_2[] = {
/* columns rows colors chars-per-pixel */
"105 26 84 1",
"  c #6A517C",
". c #7D5C76",
"X c #FF0000",
"o c #FF1805",
"O c #FF2A08",
"+ c #FF2626",
"@ c #FF3838",
"# c #FF410D",
"$ c #FF7016",
"% c #815E6F",
"& c #AD7B51",
"* c #B07851",
"= c #866370",
"- c #FF4F4F",
"; c #FF5959",
": c #DD566B",
"> c #FF7E56",
", c #FF6868",
"< c #FF7979",
"1 c #39369E",
"2 c #3736A0",
"3 c #423A97",
"4 c #4A408F",
"5 c #5C4C89",
"6 c #40409E",
"7 c #604C83",
"8 c #685482",
"9 c #4E4EAC",
"0 c #5858AF",
"q c #5D5DB4",
"w c #6060B3",
"e c #7777BE",
"r c #7D7DC3",
"t c #8676A3",
"y c #DD7C91",
"u c #FF8A1B",
"i c #DD933A",
"p c #FFA727",
"a c #FFAF3E",
"s c #FFB43C",
"d c #B48B7E",
"f c #C1844D",
"g c #D38C40",
"h c #D89140",
"j c #FFBB4F",
"k c #FFBC51",
"l c #F2BC6D",
"z c #FFC25F",
"x c #FFC464",
"c c #FFCC7A",
"v c #B99285",
"b c #FF8F8F",
"n c #FF9595",
"m c #D0A387",
"M c #D3AB93",
"N c #DDB491",
"B c #EDBF8C",
"V c #FFBF8B",
"C c #FFA0A0",
"Z c #FFB9B9",
"A c #8F8FC5",
"S c #9B9BCF",
"D c #9797D0",
"F c #A7A7D1",
"G c #B5B5DE",
"H c #DDBCD0",
"J c #FFCD83",
"K c #FFD185",
"L c #FFDE9F",
"P c #FFDCA4",
"I c #FFE0A6",
"U c #FFE4B2",
"Y c #C1C1DF",
"T c #CECEE5",
"R c #D9D9EE",
"E c #DFDFF2",
"W c #FFEFCE",
"Q c #FFF5DC",
"! c #E3E3EF",
"~ c #FFECEC",
"^ c #E8E8F8",
"/ c #FFF7E2",
"( c #FFFFFF",
") c None",
"((((((((((((((((((/csppjP((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((((Upppppppj(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"((((((((((((((((Qpppppppppj((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"((((((((((((((((kppppppppppI(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((/pppppppppppx(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((Ippppppppppps(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((",
"(((((((((((((((Ipppppppppppp((((((((((((((CXXXXXXXXXXX:1211^((((^1121R(w119((((((912F((((^1121^((((((((((",
"(((((((((((((((Upppppppppppj((((((((((((((<XXXXXXXXXXXy1112A((((A1121R(F112T((((E112!((((F1121F((((((((((",
"(((((((((((((((/pppppppppppx((((((((((((((n,,,@XXX;,,,H11126^(((12111E((211D((((A11q(((((021110((((((((((",
"((((((((((((((((cppppppppppQ((((((((((((((((((;XXX((((E11121S((D11211E((e210((((211G((((T119112Y(((((((((",
"(((((((((((((((((jppppppppc(((((((((((((((((((+XX-((((E111919((919112R((F112^((G211(((((A11Aw11A(((((((((",
"(((((((((((((((((PsppppppjQ((((((((((((((((((~XXXb((((E111A12RG12A112R(((121F((e21A(((((211EF112(((((((((",
"((((((((((WW/(((Uc(LzakcQ(x/(((WW/(((((((((((ZXXXZ((((E111^11wq10T112R(((w11q((211T((((T119(^112T((((((((",
"((((((((WW((/WQ/J((((((((((x/WQ((/WQ(((((((((bXXX(((((E111(A1121GT121R(((F112^T112(((((A11r((021A((((((((",
"(((((((W(((((((L(((((((((((WU(((((((Q((((((((;XX@(((((E111(R1212(R112R((((211DS11r(((((912STRe129((((((((",
"((((((Q(((((((((Q((((((((((Q((((((((//(((((((+XX,(((((E111((w11A(R121R((((e219012G((((R1211121112T(((((((",
"PLLLLL/(((((((((WLLLLLLLLLL((((((((((WLLLLLLVXXX>LLLLLN111LLd8 mLM112NLLLLv112111BLLLLt1121112111tLLLLLLP",
"jppppx(((((((((((sppppppppK(((((((((((pppppp$XXXupppppi121pppppppg111hppppp42111.ppppp311=*&*& 123ppppppk",
"jppppL(((((((((((zppppppppW(((((((((((zppppp#XXXppppppi121pppppppg111hppppp%2111fpppp&113pppppf112&pppppk",
"jppppL(((((((((((zppppppppW(((((((((((zpppppoXXOppppppi121pppppppg111hpppppf1124ppppp711=pppppp3115pppppz",
"jppppL(((((((((((zppppppppL(((((((((((spppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppk",
"jppppj(((((((((((pppppppppx((((((((((Qppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppk",
"jpppppQ(((((((((Lpppppppppp/(((((((((cppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppz",
"jpppppj((((((((Qpppppppppppx((((((((Wpppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppz",
"jppppppj/(((((Wsppppppppppppx/(((((Uppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppz",
"lzkzkzkzkIWWWKkzkzkzkzkzkzkzkxPWWWKkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkzkK"
};


   TImage *xpm_tmva_logo_gif_2_img = TImage::Create();
   xpm_tmva_logo_gif_2_img->SetImageBuffer( (char **)xpm_tmva_logo_gif_2, TImage::kXpm);
   xpm_tmva_logo_gif_2_img->Draw();
   imgpad__13->Modified();
   c->cd();
   c->Modified();
   c->SetSelected(c);
}
