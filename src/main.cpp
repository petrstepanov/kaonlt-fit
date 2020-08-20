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
#include "model/FitParameters.h"
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
	TH1* pmt1Hist = new TH1F("pmt1Hist", pmt1HistTitle, Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	pmt1Hist->GetXaxis()->SetTitle("Channel (ch_1)");
	pmt1Hist->GetYaxis()->SetTitle("Counts");
	TString pmt2HistTitle = TString::Format("PMT2 profile at tiler=%d", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt2Hist = new TH1F("pmt2Hist", pmt2HistTitle, Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	pmt2Hist->GetXaxis()->SetTitle("Channel (ch_2)");
	pmt2Hist->GetYaxis()->SetTitle("Counts");

	// Fill PMT histograms from the Tree data
	TreeHelper::getInstance()->fillPmtHists(pmt1Hist, pmt2Hist);

	// Plot PMT profile spectra
	if (Constants::getInstance()->parameters.plotProfiles == kTRUE){
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
		TString pngFilePath = TString::Format("%s-profiles-tile%d.png",fileName, Constants::getInstance()->parameters.tileProfile);
		pmtsCanvas->SaveAs(pngFilePath.Data());
	}

	// Trim PMT spectra to remove zero bin noise
	// Select min channel value to skip the stretched noise bin
	Int_t chMinVal = 1 * (Constants::CH_MAX_VAL - Constants::CH_MIN_VAL) / Constants::CH_BINS + 5;
	TH1* pmt1HistFit = HistUtils::cutHistogram(pmt1Hist, chMinVal, Constants::CH_FIT_MAX_VAL);
	TH1* pmt2HistFit = HistUtils::cutHistogram(pmt2Hist, chMinVal, Constants::CH_FIT_MAX_VAL);

	// Remove histogram zero values for chi2 fit
	// HistUtils::removeHistogramZeros(pmt1HistFit);
	// HistUtils::removeHistogramZeros(pmt2HistFit);

	// TCanvas* c = new TCanvas("c");
	// pmt1HistFit->Draw();

	// Fit and plot PMT spectra
	FitType fitType = Constants::getInstance()->parameters.fitType;

	const char* fitKind;
	if (fitType == FitType::root) fitKind = "ROOT Fit";
	else if (fitType == FitType::rootConv) fitKind = "ROOT Fit with Convolution";
	else fitKind = "RooFit";

	TString pmtsFitCanvasTitle = TString::Format("%s of the PMT profile spectra (tile = %d, terms = %d)", fitKind, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber);
	TCanvas* pmtsFitCanvas = new TCanvas("pmtsFitCanvas", pmtsFitCanvasTitle.Data(), 1024, 512);
	pmtsFitCanvas->Divide(2,1);

	// Retreive parameters for KaonLT Prototype histogram
	FitParameters* params = new FitParameters(ParametersType::forKaonHist);

	Int_t fitMin = 0;

	if (fitType == FitType::root){
		AbsComponentFunc* funcObject1 = new FuncSRealNoTerm0(pmt1HistFit);
		FitUtils::doFit(pmt1HistFit, params, funcObject1, fitMin, pmtsFitCanvas->cd(1), kTRUE);
		AbsComponentFunc* funcObject2 = new FuncSRealNoTerm0(pmt2HistFit);
		FitUtils::doFit(pmt2HistFit, params, funcObject2, fitMin, pmtsFitCanvas->cd(2), kTRUE);
	} else if (fitType == FitType::rootConv){
		AbsComponentFunc* funcObject1 = new FuncSRealFFTNoTerm0(pmt1HistFit);
		FitUtils::doFit(pmt1HistFit, params, funcObject1, fitMin, pmtsFitCanvas->cd(1), kTRUE);
		AbsComponentFunc* funcObject2 = new FuncSRealFFTNoTerm0(pmt2HistFit);
		FitUtils::doFit(pmt2HistFit, params, funcObject2, fitMin, pmtsFitCanvas->cd(2), kTRUE);
	} else {
		FitUtils::doRooFit(pmt1HistFit, params, kFALSE, fitMin, pmtsFitCanvas->cd(1));
		FitUtils::doRooFit(pmt2HistFit, params, kFALSE, fitMin, pmtsFitCanvas->cd(2));
	}

	// Save canvas with PMT profiles to file
	const char* fitSuffix;
	if (fitType == FitType::root) fitSuffix = "root";
	else if (fitType == FitType::rootConv) fitSuffix = "rootconv";
	else fitSuffix = "roofit";
	TString pngFitFilePath = TString::Format("%s-fit-tile%d-terms%d-%s.png", fileName, Constants::getInstance()->parameters.tileProfile, Constants::getInstance()->parameters.termsNumber, fitSuffix);
	pmtsFitCanvas->SaveAs(pngFitFilePath.Data());

	return 0;
}

// Test fit histogram digitized from the paper
int testDigitized(){
	// Get digitized histogram from paper
	TH1* h = TestSpectrum::getHistogramPaper();

	// Retreive parameters for test Bellamy histogram
	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);

	// Instantiate fitting function object
	AbsComponentFunc* funcObject = new FuncSReal(h);

	FitUtils::doFit(h, params, funcObject);
	return 0;
}

// Test fit histogram filled from the fitting function from the paper
int testFillRandom(){
	// Retreive parameters for test Bellamy histogram
	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);

	// Instantiate histogram
	// TH1* h = TestSpectrum::getHistogramPaperFix();
	TH1* h = TestSpectrum::getHistogramGenerated(params);
	// HistUtils::removeHistogramZeros(h);

	// TF1 integral for FuncSReal not matches TH1 integral...
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultAbsTolerance(1E-3);
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultRelTolerance(1E-3);
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("Gauss");
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultNPoints(n);

	// ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2");
	// ROOT::Math::MinimizerOptions::SetDefaultTolerance(1.E-3);

	// Fit histogram with ROOT Fit
	TH1* hist1 = HistUtils::cloneHistogram(h, "hist");
	AbsComponentFunc* funcObject = new FuncSReal(hist1);
	FitUtils::doFit(hist1, params, funcObject);

	// Fit histogram with ROOT Fit with Convolution
	TH1* hist2 = HistUtils::cloneHistogram(h, "hist_conv");
	AbsComponentFunc* funcObjectFFT = new FuncSRealFFT(hist2);
	FitUtils::doFit(hist2, params, funcObjectFFT);

	// Fit histogram with RooFit with Convolution
	TH1* hist3 = HistUtils::cloneHistogram(h, "hist_conv_roofit");
	FitUtils::doRooFit(hist3, params, kTRUE);

	return 0;
}

//int testNoTerm0(){
//	// Get digitized histogram from paper
//	TH1* h = TestSpectrum::getHistogramPaperNoTerm0();
//
//	// Retreive parameters for test Bellamy histogram
//	FitParameters* params = new FitParameters(ParametersType::forBellamyHist);
//
//	// Fit histogram with ROOT Fit
//	TH1* hist1 = HistUtils::cloneHistogram(h, "hist");
//	AbsComponentFunc* funcObject = new FuncSRealNoTerm0(hist1);
//	FitUtils::doFit(hist1, params, funcObject);
//
//	// Fit histogram with ROOT Fit with Convolution
//	TH1* hist2 = HistUtils::cloneHistogram(h, "hist_conv");
//	AbsComponentFunc* funcObjectFFT = new FuncSRealFFTNoTerm0(hist2);
//	FitUtils::doFit(hist2, params, funcObjectFFT);
//
//	// Fit histogram with RooFit with Convolution
//	// TH1* hist3 = HistUtils::cloneHistogram(h, "hist_conv_roofit");
//	// FitUtils::doRooFit(hist3, params, kFALSE);
//
//	return 0;
//}

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
	// testNoTerm0();

	// Iterate through input files and run analysis
	for (TObject* object : *(constants->parameters.inputFiles)) {
		if (TObjString* objString = dynamic_cast<TObjString*>(object)){
			run(objString->GetString());
		}
	}

	app->Run();
	return 0;
}
