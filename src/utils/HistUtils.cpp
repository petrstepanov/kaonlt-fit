/*
 * HistUtils.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#include "../utils/HistUtils.h"
#include <TH1F.h>

HistUtils::HistUtils() {
	// TODO Auto-generated constructor stub

}

HistUtils::~HistUtils() {
	// TODO Auto-generated destructor stub
}

TH1* HistUtils::trimHistogram(TH1* hist){

	std::cout << hist->GetNbinsX() << std::endl;
	std::cout << hist->GetXaxis()->GetBinLowEdge(1) << std::endl;
	std::cout << hist->GetXaxis()->GetBinUpEdge(hist->GetNbinsX()) << std::endl;


	Int_t minBin = hist->FindFirstBinAbove(0);
	Int_t maxBin = hist->FindLastBinAbove(0);
	Int_t nBins = maxBin - minBin + 1;

	TAxis* xAxis = hist->GetXaxis();
	TString name = TString::Format("%s-trimmed", hist->GetName());
	TString title = TString::Format("%s Trimmed", hist->GetTitle());
	TH1F* trimmedHist = new TH1F(name, title, nBins, xAxis->GetBinLowEdge(minBin), xAxis->GetBinUpEdge(maxBin));

	for (Int_t i = 1; i <= nBins; i++){
		trimmedHist->SetBinContent(i, hist->GetBinContent(i+minBin-1));
		trimmedHist->SetBinError(i, hist->GetBinError(i+minBin-1));
		std::cout << "bin: " << i << " content: " << trimmedHist->GetBinContent(i) << " error: " << trimmedHist->GetBinError(i) << std::endl;
	}

	return trimmedHist;
}

TH1* HistUtils::cutHistogram(TH1* hist, Double_t xMin, Double_t xMax){
	Int_t minBin = hist->GetXaxis()->FindBin(xMin);
	Int_t maxBin = hist->GetXaxis()->FindBin(xMax);

	Int_t nBins = maxBin - minBin + 1;

	TAxis* xAxis = hist->GetXaxis();
	TString name = TString::Format("%s-trimmed", hist->GetName());
	TString title = TString::Format("%s Trimmed", hist->GetTitle());
	TH1F* trimmedHist = new TH1F(name, title, nBins, xAxis->GetBinLowEdge(minBin), xAxis->GetBinUpEdge(maxBin));

	for (Int_t i = 1; i <= nBins; i++){
		trimmedHist->SetBinContent(i, hist->GetBinContent(i+minBin-1));
		trimmedHist->SetBinError(i, hist->GetBinError(i+minBin-1));
		std::cout << "bin: " << i << " content: " << trimmedHist->GetBinContent(i) << " error: " << trimmedHist->GetBinError(i) << std::endl;
	}

	// trimmedHist->SetEntries(trimmedHist->Integral());

	return trimmedHist;
}

TH1* HistUtils::cloneHistogram(TH1* hist, const char* newName, const char* title){
	const char* newTitle = title!=0 ? title : hist->GetTitle();

//	Int_t nBins = hist->GetXaxis()->GetNbins();
//	Int_t xMin =  hist->GetXaxis()->GetXmin();
//	Int_t xMax =  hist->GetXaxis()->GetXmax();
//
//	TH1* histClone = new TH1F(newName, newTitle, nBins, xMin, xMax);
//	for (Int_t i = 1; i <= hist->GetXaxis()->GetNbins(); i++){
//		histClone->SetBinContent(i, hist->GetBinContent(i));
//	}
//

	TH1* histClone = (TH1*)hist->Clone(newName);
	histClone->GetXaxis()->SetTitle(hist->GetXaxis()->GetTitle());
	histClone->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());

	return histClone;
}

void HistUtils::resetHistogram(TH1* hist){
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		hist->SetBinContent(i, 0);
		hist->SetBinError(i, 0);
	}
}

void HistUtils::increaseBinContent(TH1* hist, Float_t val){
	Int_t bin = hist->GetXaxis()->FindBin(val);
	if (bin >= 1 && bin <= hist->GetNbinsX()){
		Float_t content = hist->GetBinContent(bin);
		hist->SetBinContent(bin, ++content);
	}
}
