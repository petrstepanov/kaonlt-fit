/*
 * HistUtils.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#include "HistUtils.h"

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

void HistUtils::resetHistogram(TH1* hist){
	for (Int_t i = 1; i <= hist->GetNbinsX(); i++){
		hist->SetBinContent(i, 0);
		hist->SetBinError(i, 0);
	}
}
