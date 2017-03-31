
TH1F* makeDistr(TTree* t, TString var, TString name, TCut cut, int nBins, double xMin, double xMax, int color)
{  
  TH1F* h0 = new TH1F(name.Data(), name.Data(), nBins, xMin, xMax);
  TString s0(var);
  s0 += ">>";
  s0 += name;
  t->Draw(s0.Data(), cut, "goff");
  h0->Scale(1/h0->Integral());
  h0->SetLineColor(color);
  return h0;
}

void DataVsSimu() 
{
	TFile* fData = new TFile("~/godaq_rootfiles/analysis_v2.10.0/run67.root", "read"); 
	TTree* tData = (TTree*) fData->Get("tree");
	
	TFile* fSimu = new TFile("/home/ebusato/Travail/Imaging/Data/G4/MakeCrystalsFromHits_Na22_Plot4_source.root", "read"); 
	TTree* tSimu = (TTree*) fSimu->Get("tree");

	TH1F* hData_Edep = makeDistr(tData, "E", "hData_E", "", 100, 0, 1000, kBlack);
	TH1F* hSimu_Edep = makeDistr(tSimu, "EdepSmeared_Constant*1e3", "hSimu_E", "EdepSmeared_Constant*1e3>0", 100, 0, 1000, kRed);
	
	TCanvas* c1 = new TCanvas("c1", "c1");
	hData_Edep->Draw();
	hSimu_Edep->Draw("same");
}