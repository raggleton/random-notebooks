{
  gStyle->SetOptStat(0);
  TH2D * h = new TH2D("h", "Original", 25, -2, 2, 25, -2, 2);
  TF2 * xyg = new TF2("xyg","xygaus", 0, 10, 0, 10);
  xyg->SetParameters(1, 0, 1, 0, 1);
  h->FillRandom("xyg", 10000);
  TCanvas * c = new TCanvas("c", "", 600, 400);
  h->Draw("COLZ");
  c->SaveAs("orig.png");

  TH2D * hnew = (TH2D*) h->Clone("hnew");
  hnew->SetTitle("Rescaled");
  float maximum = h->GetMaximum();
  for(int i = 1; i <= h->GetNbinsX(); i++) {
    for (int j = 1; j<= h->GetNbinsY(); j++) {
      hnew->SetBinContent(i, j, h->GetBinContent(i, j) / maximum);
    }
  }
  hnew->SetMaximum(1);
  cout << h->GetMaximum() << endl; // some large number
  cout << hnew->GetMaximum() << endl; // 1
  hnew->Draw("COLZ"); // should have colourbar up to 1, but doesn't
  c->SaveAs("rescaled.png");
}