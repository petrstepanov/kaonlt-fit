#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjString.h>
#include <TStopwatch.h>

#include <Math/Factory.h>
#include <Math/Minimizer.h>
#include <Math/MinimizerOptions.h>
#include <Math/IntegratorOptions.h>

#include "model/Constants.h"
#include "utils/GraphicsUtils.h"
#include "utils/TreeUtils.h"
#include "utils/HistUtils.h"
#include "utils/TestSpectrum.h"
#include "utils/FitUtils.h"
#include "helper/TreeHelper.h"
#include "fit/FuncSReal.h"
#include "fit/FuncSRealFFT.h"
#include "fit/FuncSRealNoTerm0.h"
#include "fit/FuncSRealFFTNoTerm0.h"

int run(const char* fileName) {
	// Instantiate the Tree and read it from the input file
	if (TreeHelper::getInstance()->init(fileName) == -1){
		return -1;
	}

	// Plot the Tree if --plot-tree=kTRUE command line argument was passed
	if (Constants::getInstance()->parameters.plotTree == kTRUE){
		TreeHelper::getInstance()->plotTree(fileName);
	}

	// Temporary plot tree profiles for ch_1 and ch_2
	// Need to study the region between the pedestal and first peak
	// TreeHelper::getInstance()->plotTreeProfiles();

	// Prepare histograms for the PMT projection spectra
	TString pmt1HistTitle = TString::Format("PMT1 profile at tilel=%d", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt1Hist = new TH1F("pmt1Hist", pmt1HistTitle, Constants::CH_BINS, Constants::CH_MIN, Constants::CH_MAX);
	pmt1Hist->GetXaxis()->SetTitle("Channel (ch_1)");
	pmt1Hist->GetYaxis()->SetTitle("Counts");
	TString pmt2HistTitle = TString::Format("PMT2 profile at tiler=%d", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt2Hist = new TH1F("pmt2Hist", pmt2HistTitle, Constants::CH_BINS, Constants::CH_MIN, Constants::CH_MAX);
	pmt2Hist->GetXaxis()->SetTitle("Channel (ch_2)");
	pmt2Hist->GetYaxis()->SetTitle("Counts");

	// Fill PMT histograms from the Tree data
	TreeHelper::getInstance()->fillPmtHists(pmt1Hist, pmt2Hist);

	// Plot PMT profile spectra
	TString pmtsCanvasTitle = TString::Format("Profile of the PMT spectra (tile = %d)", Constants::getInstance()->parameters.tileProfile);
	TCanvas* pmtsCanvas = new TCanvas("pmtsCanvas", pmtsCanvasTitle.Data(), 1024, 512);
	pmtsCanvas->Divide(2,1);

	TVirtualPad* pmtsCanvasPad1 = pmtsCanvas->cd(1);
	pmtsCanvasPad1->SetLogy();
	TH1* pmt1HistClone = dynamic_cast<TH1F*>(pmt1Hist->DrawClone());
	// GraphicsUtils::alignStats(pmt1HistClone, pmtsCanvasPad1);

	TVirtualPad* pmtsCanvasPad2 = pmtsCanvas->cd(2);
	pmtsCanvasPad2->SetLogy();
	TH1* pmt2HistClone = dynamic_cast<TH1F*>(pmt2Hist->DrawClone());
	// GraphicsUtils::alignStats(pmt2HistClone, pmtsCanvasPad2);

	// Save canvas with PMT profiles to file
	TString pngFilePath = TString::Format("%s-%s-tile%d.png",fileName, pmtsCanvas->GetName(), Constants::getInstance()->parameters.tileProfile);
	pmtsCanvas->SaveAs(pngFilePath.Data());

	// Trim PMT spectra to remove zero bin noise
	TH1* pmt1HistFit = HistUtils::cutHistogram(pmt1Hist, Constants::CH_FIT_MIN, Constants::CH_FIT_MAX);
	TH1* pmt2HistFit = HistUtils::cutHistogram(pmt2Hist, Constants::CH_FIT_MIN, Constants::CH_FIT_MAX);

	// Fit and plot PMT spectra
	const char* fitKind = Constants::getInstance()->parameters.rooFit ? "RooFit" : "Fit";
	TString pmtsFitCanvasTitle = TString::Format("%s of the PMT profile spectra (tile = %d, terms = %d)", fitKind, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber);
	TCanvas* pmtsFitCanvas = new TCanvas("pmtsFitCanvas", pmtsFitCanvasTitle.Data(), 1024, 512);
	pmtsFitCanvas->Divide(2,1);

	if (Constants::getInstance()->parameters.rooFit){
		// TODO: separate roofit Pdf cration into a provider? will speed up?
		FitUtils::doRooFit(pmt1HistFit, kFALSE, pmtsFitCanvas->cd(1));
		FitUtils::doRooFit(pmt2HistFit, kFALSE, pmtsFitCanvas->cd(2));
	} else {
		AbsComponentFunc* funcObjectFFT1 = new FuncSRealFFT(pmt1HistFit);
		FitUtils::doFit(pmt1HistFit, funcObjectFFT1, pmtsFitCanvas->cd(1));
		AbsComponentFunc* funcObjectFFT2 = new FuncSRealFFT(pmt2HistFit);
		FitUtils::doFit(pmt2HistFit, funcObjectFFT2, pmtsFitCanvas->cd(2));
	}

	// Save canvas with PMT profiles to file
	const char* fitType = Constants::getInstance()->parameters.rooFit ? "-roofit" : "";
	TString pngFitFilePath = TString::Format("%s-%s-tile%d-terms%d%s.png",fileName, pmtsCanvas->GetName(), Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber, fitType);
	pmtsCanvas->SaveAs(pngFitFilePath.Data());

	return 0;
}

// Test fit histogram digitized from the paper
int testDigitized(){
	TH1* hist = TestSpectrum::getHistogramPaper();
	AbsComponentFunc* funcObject = new FuncSReal(hist);
	FitUtils::doFit(hist, funcObject);
	return 0;
}

// Test fit histogram filled from the fitting function from the paper
int testFillRandom(){
	// Instantiate histogram
	Int_t nBins = TestSpectrum::getHistogramPaper()->GetXaxis()->GetNbins();
	TH1F *hist = new TH1F("hist", "Bellamy histogram. Random fill from fit function.", nBins, 0, nBins);
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");
	AbsComponentFunc* funcObject = new FuncSReal(hist);
	FitUtils::fillHistogramFromFuncObject(hist, funcObject);

	// Fit histogram with ROOT Fit with Convolution
	TH1* hist2 = HistUtils::cloneHistogram(hist, "hist_conv");
	AbsComponentFunc* funcObjectFFT = new FuncSRealFFT(hist2);
	FitUtils::doFit(hist2, funcObjectFFT);

	// Fit histogram with RooFit with Convolution
	TH1* hist3 = HistUtils::cloneHistogram(hist, "hist_conv_roofit");
	FitUtils::doRooFit(hist3, kTRUE);

	return 0;
}

int testRebin(){
	// Instantiate histogram
	Int_t nBins = TestSpectrum::getHistogramPaper()->GetXaxis()->GetNbins();
	TH1F *hist = new TH1F("hist", "Bellamy histogram. Random fill from fit function.", nBins, 0, nBins);
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");
	AbsComponentFunc* funcObject = new FuncSReal(hist);
	FitUtils::fillHistogramFromFuncObject(hist, funcObject);

	// Fit histogram with ROOT Fit with Convolution
	TH1* hist2 = HistUtils::cloneHistogram(hist, "hist_conv");
	AbsComponentFunc* funcObjectFFT = new FuncSRealFFT(hist2);
	FitUtils::doFit(hist2, funcObjectFFT);

	// Fit histogram with RooFit with Convolution
	TH1* hist3 = HistUtils::cloneHistogram(hist, "hist_conv_roofit");
	FitUtils::doRooFit(hist3, kTRUE);

	return 0;
}


int main(int argc, char* argv[]) {
	// Create ROOT application
	// https://github.com/root-project/root/blob/master/tutorials/gui/mditest.C#L409
	TApplication* app = new TApplication(Constants::APPLICATION_NAME, &argc, argv);

	// Parse command-line parameters
	// TApplication::TApplication() modifies the original list of parameters
	// Need to use ROOT's gApplication->Argc() and gApplication->Argv();
	Constants* constants = Constants::getInstance();
	constants->parseParameters(gApplication->Argc(), gApplication->Argv());

	// Check if input files are provided
	if (constants->parameters.inputFiles->GetSize() < 1){
		std::cout << "No spectra files specified." << std::endl;
		return 1;
	}

	// Test fitting function on the digitized test histogram
	// testDigitized();
	// Test fitting function on the filled random test histogram
	// testFillRandom();

	// Iterate through input files and run analysis
	for (TObject* object : *(constants->parameters.inputFiles)) {
		if (TObjString* objString = dynamic_cast<TObjString*>(object)){
			run(objString->GetString());
		}
	}

	app->Run();
	return 0;
}
