#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TObjString.h>

#include "model/Constants.h"
#include "utils/FitUtils.h"
#include "utils/GraphicsUtils.h"
#include "utils/TreeUtils.h"
#include "utils/TestSpectrum.h"
#include "helper/TreeHelper.h"

int run(const char* fileName) {
	// Instantiate the Tree and read it from the input file
	if (TreeHelper::getInstance()->init(fileName) == -1){
		return -1;
	}

	// Plot the Tree if --plot-tree=kTRUE command line argument was passed
	if (Constants::getInstance()->parameters.plotTree == kTRUE){
		TreeHelper::getInstance()->plotTree();
	}

	// Temporary plot tree profiles for ch_! and ch_2
	// Need to study the region between the pedestal and first peak
	// TreeHelper::getInstance()->plotTreeProfiles();

	// Prepare histograms for the PMT projection spectra
	TString pmt1HistTitle = TString::Format("PMT1 profile at tilel=%d", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt1Hist = new TH1F("pmt1Hist", pmt1HistTitle, 2100, -1000, 20000);
	pmt1Hist->GetXaxis()->SetTitle("Channel (ch_1)");
	pmt1Hist->GetYaxis()->SetTitle("Counts");
	TString pmt2HistTitle = TString::Format("PMT2 profile at tiler=%d", Constants::getInstance()->parameters.tileProfile);
	TH1* pmt2Hist = new TH1F("pmt2Hist", pmt2HistTitle, 2100, -1000, 20000);
	pmt2Hist->GetXaxis()->SetTitle("Channel (ch_2)");
	pmt2Hist->GetYaxis()->SetTitle("Counts");

	// Fill PMT histograms from the Tree data
	TreeHelper::getInstance()->fillPmtHists(pmt1Hist, pmt2Hist);

	// Plot PMT profile spectra
	TString pmtsCanvasTitle = TString::Format("Profile of the PMT spectra (tile = %d)", Constants::getInstance()->parameters.tileProfile);
	TCanvas* pmtsCanvas = new TCanvas("pmtsCanvas", pmtsCanvasTitle, 1024, 512);
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
	TString pngFilePath = TString(pmtsCanvas->GetName()) + ".png";
	pmtsCanvas->SaveAs(pngFilePath);

	// Perform fitting (just one hist for now)
	TF1* fitFunction = FitUtils::getRealFitFunction(pmt1Hist);
	TCanvas* fitCanvas = new TCanvas("fitCanvas", "fitCanvas", 1024, 512);
	fitCanvas->SetLogy();
	pmt1Hist->Fit(fitFunction->GetName());
	GraphicsUtils::showFitParametersInStats(pmt1Hist, fitCanvas);
	pmt1Hist->Draw();
	GraphicsUtils::alignStats(pmt1Hist, fitCanvas);

	return 0;
}

int test(){
	TH1* testHist = TestSpectrum::getHistogram();
	TCanvas* testCanvas = new TCanvas("testCanvas", "testCanvas", 640, 512);
	TF1* fitFunction = FitUtils::getRealFitFunction(testHist);
//	testHist->Fit(fitFunction->GetName());
//	GraphicsUtils::showFitParametersInStats(testHist, testCanvas);
	testHist->Draw();
	fitFunction->Draw("SAME");
	GraphicsUtils::alignStats(testHist, testCanvas);
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

	// Test fitting function on the test histigram
	test();

	// Iterate through input files and run analysis
//	for (TObject* object : *(constants->parameters.inputFiles)) {
//		if (TObjString* objString = dynamic_cast<TObjString*>(object)){
//			run(objString->GetString());
//		}
//	}

	app->Run();
	return 0;
}
