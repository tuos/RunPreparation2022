void fig(){

  //TFile *infile = new TFile(Form("HF_eff.root"),"read");
  TFile *infile = new TFile(Form("hf_L1HF_corr_2023_8.root"),"read");

  TH1F* num9472lx2;
  TH1F* num9094lx2;
  TH1F* num9400lx;
  TH1F* num9100lx;
  TH1F* num9480;
  TH1F* num9160;
  TH1F* num9621c;
  TH1F* num9325c;
  TH1F* num9273m;
  TH1F* num9546m;
  TH1F* den;

  num9472lx2 = (TH1F*)infile->Get(Form("h_num9472lx2"));
  num9094lx2 = (TH1F*)infile->Get(Form("h_num9094lx2"));
  num9400lx = (TH1F*)infile->Get(Form("h_num9400lx"));
  num9100lx = (TH1F*)infile->Get(Form("h_num9100lx"));
  num9480 = (TH1F*)infile->Get(Form("h_num9480"));
  num9160 = (TH1F*)infile->Get(Form("h_num9160"));
  num9621c = (TH1F*)infile->Get(Form("h_num9621c"));
  num9325c = (TH1F*)infile->Get(Form("h_num9325c"));
  num9273m = (TH1F*)infile->Get(Form("h_num9273m"));
  num9546m = (TH1F*)infile->Get(Form("h_num9546m"));
  den = (TH1F*)infile->Get(Form("h_den"));

 TCanvas *c1 = new TCanvas("c1","c1",1,1,550*1.1,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.06);
  c1->SetRightMargin(0.02);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,3000.,7999.);
 hist->SetXTitle("Offline HFsum (GeV)");
 hist->SetYTitle("Trigger Efficiency (L1 + HLT)");
 hist->SetMinimum(-0.009);
 hist->SetMaximum(1.09);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.15);
 hist->GetXaxis()->SetTitleOffset(1.05);
 hist->GetXaxis()->SetTitleSize(0.06);
 hist->GetYaxis()->SetTitleSize(0.06);
 hist->GetXaxis()->SetLabelSize(0.045);
 hist->GetYaxis()->SetLabelSize(0.045);
 hist->GetXaxis()->SetNdivisions(505);
 hist->Draw();

  TGraphAsymmErrors *gr1 = new TGraphAsymmErrors();
  gr1->BayesDivide(num9094lx2,den);
  gr1->SetMarkerColor(kBlack);
  gr1->SetLineColor(kBlack);
  gr1->SetMarkerStyle(kOpenSquare);
  gr1->SetMarkerSize(1.1);
  gr1->Draw("pLsameez");

  TGraphAsymmErrors *gr2 = new TGraphAsymmErrors();
  gr2->BayesDivide(num9472lx2,den);
  gr2->SetMarkerColor(kRed);
  gr2->SetLineColor(kRed);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.1);
  gr2->Draw("pLsameez");

TLine *line1 = new TLine(4394.49, 0, 4394.49, 1);
line1->SetLineColor(1);
line1->SetLineWidth(2);
line1->SetLineStyle(2);
//line1->Draw();
TLine *line2 = new TLine(5156.88, 0, 5156.88, 1);
line2->SetLineColor(1);
line2->SetLineWidth(2);
line2->SetLineStyle(1);
line2->Draw();
TLine *line3 = new TLine(5302.01, 0, 5302.01, 1);
line3->SetLineColor(2);
line3->SetLineWidth(2);
line3->SetLineStyle(2);
line3->Draw();

TLine *line3x = new TLine(3000, 1.00, 7999, 1.0);
line3x->SetLineColor(1);
line3x->SetLineWidth(2);
line3x->SetLineStyle(2); 
line3x->Draw();

    TLegend *leg = new TLegend(0.2,0.45,0.38,0.6);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.045);
    //leg->AddEntry(line1,"Top 1.5%","l");
    leg->AddEntry(line2,"GO Top 1.0%","l");
    leg->AddEntry(line3,"GO Top 0.5%","l");
    leg->Draw();

    TLegend *leg2 = new TLegend(0.2,0.7,0.38,0.85);
    leg2->SetFillColor(10);
    leg2->SetBorderSize(0);
    leg2->SetTextFont(42);
    leg2->SetTextColor(1);
    leg2->SetTextSize(0.045);
    leg2->AddEntry(gr1,"UCC_0_1","pl");
    leg2->AddEntry(gr2,"UCC_0_0p5","pl");
    leg2->Draw();

   TLatex *   tex = new TLatex(0.65,0.955,"PbPb 5.36 TeV UCC");
   tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   //TLatex *   tex2 = new TLatex(0.64,0.21,"Run 374354");
   TLatex *   tex2 = new TLatex(0.15,0.955,"CMS");
   tex2->SetNDC();
   tex2->SetTextFont(62);
   tex2->SetTextSize(0.045);
   tex2->SetLineWidth(2);
   tex2->Draw();
   TLatex *   tex2b = new TLatex(0.24,0.955,"Preliminary");
   tex2b->SetNDC();
   tex2b->SetTextFont(52);
   tex2b->SetTextSize(0.045);
   tex2b->SetLineWidth(2);
   tex2b->Draw();

   TLatex *   tex3 = new TLatex(0.64,0.44,"L1 1%, 9094");
   tex3->SetNDC();
   tex3->SetTextFont(42);
   tex3->SetTextSize(0.045);
   tex3->SetLineWidth(2);
   //tex3->Draw();
   TLatex *   tex4 = new TLatex(0.64,0.38,"L1 0.5%, 9472");
   tex4->SetNDC();
   tex4->SetTextFont(42);
   tex4->SetTextSize(0.045);
   tex4->SetTextColor(2);
   tex4->SetLineWidth(2);
   //tex4->Draw();


  c1->Print("plot_UCC_eff.C");
  c1->Print("plot_UCC_eff.png");
  c1->Print("plot_UCC_eff.pdf");

}
