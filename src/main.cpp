#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include <iostream>
#include <TFile.h>
//
//struct Spectrum {
//	TString filename;
//	TH1F* histogram;              // ROOT histogram
//	RooDataHist* dataHistogram;   // RooFit histogram
//	Double_t integral;            // total counts
//	Int_t numberOfBins;
//	Int_t binWithMinimumCount;    // bin number with minimum value in the range
//	Int_t binWithMaximumCount;    // bin number with maximum value in the range
//	Double_t minimumCount;        // minimum count across all bins
//	Double_t maximu1mCount;        // maximum count across all bins
//	Double_t averageBackground;
//	RooAbsPdf* model;
//};


int main(int argc, char* argv[]) {
	// Check if spectra filenames are passed as parameters
	if(argc == 1){
		std::cout << "No spectra files specified." << std::endl;
		exit(-1);
	}

	// Iterate through parameters and fit every spectrum
	for (int i = 1; i < argc; i++){
		TFile* file = new TFile(argv[i]);
		if (file->IsZombie()) {
			std::cout << "Error opening file \"" << argv[i] << "\""<< std::endl;
			exit(-1);
		} else {
			file->Map();

			file->ShowStreamerInfo();
		}
	}
	return 0;
}
