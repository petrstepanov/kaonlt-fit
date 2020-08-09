/*
 * FitUtils.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FitUtils.h"
#include "../fit/FuncSReal.h"
#include "../fit/FuncSRealFFT.h"
#include "../roofit/Term0Pdf.h"
#include "../roofit/SIdealNPdf.h"
#include "../roofit/SRealNPdf.h"
#include "../roofit/BPdf.h"
#include "../model/Constants.h"
#include "../utils/RootUtils.h"
#include "../utils/GraphicsUtils.h"
#include <RooRealVar.h>
#include <RooConstVar.h>
#include <RooDataHist.h>
#include <RooFFTConvPdf.h>
#include <RooNumConvPdf.h>
#include <RooAddPdf.h>
#include <RooChi2Var.h>
#include <RooMinimizer.h>
#include <RooPlot.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>

FitUtils::FitUtils() {
}

FitUtils::~FitUtils() {
}

// Parameter values taken from Fig.2, https://doi.org/10.1016/0168-9002(94)90183-X
RooRealVar* FitUtils::Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10, 40, "e");
RooRealVar* FitUtils::s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0.1, 10, "");
RooRealVar* FitUtils::Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 0, 100, "e");
RooRealVar* FitUtils::s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 5, 50, "");
RooRealVar* FitUtils::w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.4, 0.1, 1, "");
RooRealVar* FitUtils::a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0, 0.1, "");
RooRealVar* FitUtils::mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 0, 20, "");

void FitUtils::doFit(TH1* hist){
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;
	TF1* func = getFuncSReal(hist, nTerms, kFALSE);

	// Set default integrator
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("");

	// Tutorial: /fit/NumericalMinimization.C
	//	const char* minName = "Minuit2";
	//	const char* algoName = "";
	//	ROOT::Math::Minimizer* minimizer = ROOT::Math::Factory::CreateMinimizer(minName, algoName);
	//
	//	minimizer->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
	//	minimizer->SetMaxIterations(10000);  // for GSL
	//	minimizer->SetTolerance(0.001);
	//	minimizer->SetPrintLevel(1);

	//	ROOT::Math::MinimizerOptions::SetDefaultStrategy(0);

	hist->Fit(func, "V");

	TCanvas* canvas = new TCanvas("canvas", "testCanvas", 640, 512);
	GraphicsUtils::showFitParametersInStats(hist, canvas);
	hist->Draw();
	//	func->Draw("SAME");
	GraphicsUtils::alignStats(hist, canvas);
}

// Fit not goes, weird function raise to the right
void FitUtils::doRooFit(TH1* hist){
	// Define channels axis (observable)
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	RooRealVar* observable = new RooRealVar("observable", "ADC channel", xMin, xMax, "");

	// Set observable binning and convolution binning
	observable->setBins(hist->GetNbinsX());
	observable->setBins(4096, "cache");

	// Instantiate list of PDF terms
	RooArgList* terms = new RooArgList();
	RooArgList* coefficients = new RooArgList();

	// Init terms 1..N as convolution of the background and ideal PM response function
//	BPdf* bPdf = new BPdf("bPdf", "Background", *observable, *Q0, *s0, *w, *a);
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n = 1; n < nTerms; n++){
		// Instantiate N-th component PDF
		TString nameN = TString::Format("n%d", n);
		TString titleN = TString::Format("Term index %d", n);
		RooConstVar* nVar = new RooConstVar(nameN.Data(), titleN.Data(), (Double_t)n);

		TString name = TString::Format("sIdeal%dPdf", n);
		TString title = TString::Format("Term %d or the ideal PM function", n);
		SIdealNPdf* sIdealNPdf = new SIdealNPdf(name.Data(), title.Data(), *observable, *Q1, *s1, *mu, *nVar);

		// Instantiate background PDF
		 TString nameB = TString::Format("B%dPdf", n);
		 TString titleB = TString::Format("Background PDF %d", n);
		 BPdf* bPdf = new BPdf(nameB.Data(), titleB.Data(), *observable, *Q0, *s0, *w, *a);

		// Convolute ideal function with the background
		TString nameConv = TString::Format("term%dPdf", n);
		TString titleConv = TString::Format("Term %d or the real PM function", n);
		RooFFTConvPdf* termNPdf = new RooFFTConvPdf(nameConv.Data(), titleConv.Data(), *observable, *sIdealNPdf, *bPdf);
		termNPdf->setBufferFraction(10);
		termNPdf->setBufferStrategy(RooFFTConvPdf::Flat);

//		RooNumConvPdf* termNPdf = new RooNumConvPdf(nameConv.Data(), titleConv.Data(), *observable, *sIdealNPdf, *bPdf);
//		RooConstVar* convCenter = new RooConstVar("convCenter", "Convolution window center", (xMin+xMax)/2);
//		RooConstVar* convWidth = new RooConstVar("convWidth", "Convolution window width", (xMin+xMax)/2);
//		termNPdf->setConvolutionWindow(*convCenter, *convWidth);

		// Set buffer fraction so tail not piles on the start
		terms->add(*termNPdf);
	}

	// Init zero term PDF:
	Term0Pdf* term0Pdf = new Term0Pdf("term0Pdf", "Term 0 of the real PM function", *observable, *Q0, *s0, *w, *a, *mu);
	terms->add(*term0Pdf);

	// Define the N coefficients for the terms (each is 1/nTerms)
	for (UInt_t n = 0; n < nTerms; n++){
		TString name = TString::Format("term%dCoeff", n);
		TString title = TString::Format("Term %d coefficient", n);
		// RooConstVar* termNCoeff = new RooConstVar(name.Data(), title.Data(), (Double_t)1.);
		RooRealVar* termNCoeff = new RooRealVar(name.Data(), title.Data(), 1.0, 1.0, 1.0, "");
		termNCoeff->setConstant();
		coefficients->add(*termNCoeff);
	}

	// Sum terms of the real PM responce function
	// RooAddPdf* sRealPdf = new RooAddPdf("sRealPdf", "Real PM responce function", *terms, *coefficients);
	RooAddPdf* sRealPdf = new RooAddPdf("sRealPdf", "Real PM responce function", *terms, *coefficients);
	sRealPdf->fixAddCoefNormalization(RooArgSet(*observable));

	terms->Print("V");
	coefficients->Print("V");

	// Prepare data histogram
	RooDataHist* data = new RooDataHist("data", "Dataset", RooArgList(*observable), hist);

	// Chi2 fit
	RootUtils::startTimer();  // Start tracking Time
	// RooChi2Var* chi2 = new RooChi2Var("chi2", "chi2", *sRealPdf, *data, RooFit::NumCPU(RootUtils::getNumCpu()));
	// RooMinimizer* m = new RooMinimizer(*chi2);
	// m->setMinimizerType("Minuit2");
	// Int_t resultMigrad = m->migrad();
	// Int_t resultHesse = m->hesse();
	// RooFitResult* fitResult = m->save();


	// Unbinned likelihood fit
	RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setRealValue("maxSteps", 30);
	sRealPdf->fitTo(*data);

	// Construct and mimimize unbinned likelihood
	// RooAbsReal *nll = model.createNLL(*data, NumCPU(2));
	// RooMinimizer(*nll).migrad();


	// Create RooPlot from energy axis frame
	RooPlot* spectrumPlot = observable->frame();
	spectrumPlot->SetTitle("");  // Set Empty Graph Title
	// spectrumPlot->GetXaxis()->SetRangeUser(fitRangeMin, fitRangeMax);      // Do we need this?

	// Configure axis labels and look
	GraphicsUtils::styleAxis(spectrumPlot->GetXaxis(), "ADC channel", 1.5, 0.02, kTRUE); // Title, Title offset, Label offset
	GraphicsUtils::styleAxis(spectrumPlot->GetYaxis(), "Counts", 1.1, 0.012, kTRUE);

	// Plot data points
	data->plotOn(spectrumPlot, RooFit::LineColor(kGray + 3), /*RooFit::ShiftToZero(),*/ RooFit::XErrorSize(0), RooFit::MarkerSize(0.5), RooFit::MarkerColor(kGray + 3), RooFit::Name("data"));

	// bPdf->plotOn(spectrumPlot);

	sRealPdf->plotOn(spectrumPlot);

	// Plot model components
	// Problem: convoluted PDF loses normalization of components
	// TODO: normalize components on (1-source contribution) relative!
	sRealPdf->getComponents()->Print("V");
	{
		RooArgSet* components = sRealPdf->getComponents();
		TIterator* it = components->createIterator();
		UInt_t i = 0;
		// Here we have to normalize non-convoluted material components with respect to the source contribution!
		while (TObject* tempObject = it->Next()) {
			RooAbsPdf* component = dynamic_cast<RooAbsPdf*>(tempObject);
			if (component && (strcmp(component->ClassName(),"Term0Pdf")==0 || strcmp(component->ClassName(),"RooFFTConvPdf")==0)) {
				sRealPdf->plotOn(spectrumPlot, RooFit::Components(*component), RooFit::LineStyle(kDashed), RooFit::LineColor(GraphicsUtils::colorSet[i++%GraphicsUtils::colorSet.size()]));
				// legend->AddEntry(spectrumPlot->findObject(component->GetName()), component->GetTitle(), "l");
			}
			if (component && strcmp(component->ClassName(),"BPdf")==0) {
				sRealPdf->plotOn(spectrumPlot, RooFit::Components(*component), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
				// legend->AddEntry(spectrumPlot->findObject(component->GetName()), component->GetTitle(), "l");
			}
		}
	}

	spectrumPlot->Draw();
}

// Fit without convolution, with SRealNPdf
void FitUtils::doRooFit2(TH1* hist){
	// Define channels axis (observable)
	RooRealVar* observable = new RooRealVar("observable", "Channels axis", hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax(), "ch");

	// Set observable binning and convolution binning
	observable->setBins(hist->GetNbinsX());
	observable->setBins(4096, "cache");

	// Instantiate list of PDF terms
	RooArgList* terms = new RooArgList();
	RooArgList* coefficients = new RooArgList();

	// Init zero term PDF:
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;
	Term0Pdf* term0Pdf = new Term0Pdf("term0Pdf", "Term 0 of the real PM function", *observable, *Q0, *s0, *w, *a, *mu);
	terms->add(*term0Pdf);

	// Init terms 1..N as convolution of the background and ideal PM response function
	BPdf* bPdf = new BPdf("bPdf", "Background", *observable, *Q0, *s0, *w, *a);
	for (UInt_t n = 1; n < nTerms; n++){
		// Instantiate N-th component PDF
		TString nameN = TString::Format("n%d", n);
		TString titleN = TString::Format("Term index %d", n);
		RooConstVar* nVar = new RooConstVar(nameN.Data(), titleN.Data(), (Double_t)n);

		TString name = TString::Format("sIdeal%dPdf", n);
		TString title = TString::Format("Term %d or the ideal PM function", n);
		SRealNPdf* sRealNPdf = new SRealNPdf(name.Data(), title.Data(), *observable, *Q0, *Q1, *s1, *w, *a, *mu, *nVar);
		terms->add(*sRealNPdf);
	}

	// Define the N coefficients for the terms (each is 1/nTerms)
	for (UInt_t n = 0; n < nTerms; n++){
		TString name = TString::Format("term%dCoeff", n);
		TString title = TString::Format("Term %d coefficient", n);
		// RooConstVar* termNCoeff = new RooConstVar(name.Data(), title.Data(), (Double_t)1.);
		RooRealVar* termNCoeff = new RooRealVar(name.Data(), title.Data(), 1.0, 1.0, 1.0, "");
		termNCoeff->setConstant();
		coefficients->add(*termNCoeff);
	}

	// Sum terms of the real PM responce function
	RooAddPdf* sRealPdf = new RooAddPdf("sRealPdf", "Real PM responce function", *terms, *coefficients);
	sRealPdf->fixAddCoefNormalization(RooArgSet(*observable));

	terms->Print("V");
	coefficients->Print("V");

	// Prepare data histogram
	RooDataHist* data = new RooDataHist("data", "Dataset", RooArgList(*observable), hist);

	// Chi2 fit
	RootUtils::startTimer();  // Start tracking Time
	// RooChi2Var* chi2 = new RooChi2Var("chi2", "chi2", *sRealPdf, *data, RooFit::NumCPU(RootUtils::getNumCpu()));
	// RooMinimizer* m = new RooMinimizer(*chi2);
	// m->setMinimizerType("Minuit2");
	// Int_t resultMigrad = m->migrad();
	// Int_t resultHesse = m->hesse();
	// RooFitResult* fitResult = m->save();


	// Unbinned likelihood fit
	RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setRealValue("maxSteps", 30);
	sRealPdf->fitTo(*data);

	// Construct and mimimize unbinned likelihood
	// RooAbsReal *nll = model.createNLL(*data, NumCPU(2));
	// RooMinimizer(*nll).migrad();


	// Create RooPlot from energy axis frame
	RooPlot* spectrumPlot = observable->frame();
	spectrumPlot->SetTitle("");  // Set Empty Graph Title
	// spectrumPlot->GetXaxis()->SetRangeUser(fitRangeMin, fitRangeMax);      // Do we need this?

	// Configure axis labels and look
//	GraphicsUtils::styleAxis(spectrumPlot->GetYaxis(), "Counts", 1.1, 0.012, kTRUE);
//	GraphicsUtils::styleAxis(spectrumPlot->GetXaxis(), "ADC channel", 1.5, 0.02, kTRUE); // Title, Title offset, Label offset

	// Plot data points
	data->plotOn(spectrumPlot, RooFit::LineColor(kGray + 3), /*RooFit::ShiftToZero(),*/ RooFit::XErrorSize(0), RooFit::MarkerSize(0.5), RooFit::MarkerColor(kGray + 3), RooFit::Name("data"));

	// bPdf->plotOn(spectrumPlot);

	sRealPdf->plotOn(spectrumPlot);

	// Plot model components
	// Problem: convoluted PDF loses normalization of components
	// TODO: normalize components on (1-source contribution) relative!
	sRealPdf->getComponents()->Print("V");
	{
		RooArgSet* components = sRealPdf->getComponents();
		TIterator* it = components->createIterator();
		UInt_t i = 0;
		// Here we have to normalize non-convoluted material components with respect to the source contribution!
		while (TObject* tempObject = it->Next()) {
			RooAbsPdf* component = dynamic_cast<RooAbsPdf*>(tempObject);
			if (component && (strcmp(component->ClassName(),"Term0Pdf")==0 || strcmp(component->ClassName(),"RooFFTConvPdf")==0)) {
				sRealPdf->plotOn(spectrumPlot, RooFit::Components(*component), RooFit::LineStyle(kDashed), RooFit::LineColor(GraphicsUtils::colorSet[i++%GraphicsUtils::colorSet.size()]));
				// legend->AddEntry(spectrumPlot->findObject(component->GetName()), component->GetTitle(), "l");
			}
			if (component && strcmp(component->ClassName(),"BPdf")==0) {
				sRealPdf->plotOn(spectrumPlot, RooFit::Components(*component), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlack));
				// legend->AddEntry(spectrumPlot->findObject(component->GetName()), component->GetTitle(), "l");
			}
		}
	}

	spectrumPlot->Draw();
}

TF1* FitUtils::getFuncSReal(TH1* hist, Int_t nMax, Bool_t isFFT){
	// Init array of ROOT parameters for single function
	RooArgList* parameters = new RooArgList();
	parameters->add(*Q0);
	parameters->add(*s0);
	parameters->add(*Q1);
	parameters->add(*s1);
	parameters->add(*w);
	parameters->add(*a);
	parameters->add(*mu);

	// Instantiate fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();

	// Experiencing memory leaks if define fitFunction inside FuncSReal like:
	// fitFunction = new TF1("fitFunction", this, &FuncSRealOld::func, xMin, xMax, nPar, "FuncSRealOld", "func");

	// Therefore we instantiate it in the FitUtils
	TF1* fitFunction;
	if(isFFT){
		FuncSRealFFT* funcSRealFFT = new FuncSRealFFT(hist, nMax);
		fitFunction = new TF1("fitFunction", funcSRealFFT, &FuncSRealFFT::func, xMin, xMax, parameters->size());

	} else {
		FuncSReal* funcSReal = new FuncSReal(hist, nMax);
		fitFunction = new TF1("fitFunction", funcSReal, &FuncSReal::func, xMin, xMax, parameters->size());
	}

	// Set function starting parameter values, names and limits
	TIterator* it = parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			fitFunction->SetParName(i, parameter->GetName());
			fitFunction->SetParameter(i, parameter->getVal());
			fitFunction->SetParLimits(i, parameter->getMin(), parameter->getMax());
			i++;
		}
	}

	fitFunction->SetNpx(1000);
	return fitFunction;
}
