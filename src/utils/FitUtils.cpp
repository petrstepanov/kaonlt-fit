/*
 * FitUtils.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FitUtils.h"
#include "../fit/FuncSReal.h"
#include "../fit/FuncSRealFFT.h"
#include "../fit/components/FuncTerm0.h"
#include "../fit/components/FuncTermN.h"
#include "../roofit/Term0Pdf.h"
#include "../roofit/SIdealNPdf.h"
#include "../roofit/SRealNPdf.h"
#include "../roofit/BPdf.h"
#include "../roofit/ExpPdf.h"
#include "../roofit/GaussPdf.h"
#include "../model/Constants.h"
#include "../utils/RootUtils.h"
#include "../utils/GraphicsUtils.h"
#include "../utils/HistUtils.h"
#include "../helper/TF1Normalize.h"
#include <RooRealVar.h>
#include <RooConstVar.h>
#include <RooAbsCollection.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooFFTConvPdf.h>
#include <RooNumConvPdf.h>
#include <RooAddPdf.h>
#include <RooArgList.h>
#include <RooChi2Var.h>
#include <RooFormulaVar.h>
#include <RooMinimizer.h>
#include <RooPlot.h>
#include <RooGaussian.h>
#include <RooRealSumPdf.h>
#include <RooRealSumFunc.h>
#include <TF1.h>
#include <TAttLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TVectorD.h>
#include <TPaveText.h>
#include <TCollection.h>
#include <TFitResultPtr.h>
#include <TDatime.h>
#include <Math/IntegratorOptions.h>
#include <TSystem.h>

FitUtils::FitUtils() {
}

FitUtils::~FitUtils() {
}

// Fit not goes, weird function raise to the right
void FitUtils::doRooFit(TH1* hist, FitParameters* pars, Bool_t useTerm0, Int_t fitMin, TVirtualPad* pad){
	TDatime* timestamp = new TDatime();

	// Define channels axis (observable)
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	RooRealVar* observable = new RooRealVar("observable", "ADC channel", xMin, xMax, "");

	// Set observable binning and convolution binning
	observable->setBins(hist->GetNbinsX());
	observable->setBins(Constants::getInstance()->parameters.convolutionBins, "cache");

	// Instantiate list of PDF terms
	RooArgList* terms = new RooArgList();
	RooArgList* coefficients = new RooArgList();

	// Init zero term PDF (it's also a background function - paper has mistake - needs shifted):
	// RooGaussian* gauss = new RooGaussian("gauss", "gaussian PDF", *observable, *Constants::Q0, *Constants::s0);
	// ExpPdf* exp = new ExpPdf("exp", "exponential PDF", *observable, *Constants::Q0, *Constants::a);
	// RooAddPdf* term0Pdf = new RooAddPdf("term0Pdf", "Term 0 of the real PM function", RooArgList(*exp, *gauss), RooArgList(*Constants::w), kTRUE);

	// TIP: cannot use the same function to convolute other components
	if (useTerm0){
		BPdf* term0 = new BPdf("term0", "Background function shifted", *observable, *(pars->Q0), *(pars->s0), *(pars->w), *(pars->a));
		terms->add(*term0);
		RooFormulaVar* coeff0 = new RooFormulaVar("coeff0", "Term 0 coefficient", "exp(-@0)", RooArgList(*(pars->mu)));
		coefficients->add(*coeff0);
	}

	// Init terms 1..N as convolution of the background and ideal PM response function
	BPdf* bPdf = new BPdf("bPdf", "Background", *observable, *(pars->Q0), *(pars->s0), *(pars->w), *(pars->a));
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n = 1; n < nTerms; n++){
		// Instantiate N-th component PDF
		TString nameN = TString::Format("n%d", n);
		TString titleN = TString::Format("Term index %d", n);
		RooConstVar* nVar = new RooConstVar(nameN.Data(), titleN.Data(), (Double_t)n);

		TString name = TString::Format("sIdeal%dPdf", n);
		TString title = TString::Format("Term %d or the ideal PM function", n);
		SIdealNPdf* sIdealNPdf = new SIdealNPdf(name.Data(), title.Data(), *observable, *(pars->Q1), *(pars->s1), *nVar);

		// Convolute ideal function with the background
		TString nameConv = TString::Format("term%dPdf", n);
		TString titleConv = TString::Format("Term %d or the real PM function", n);
		RooFFTConvPdf* termNPdf = new RooFFTConvPdf(nameConv.Data(), titleConv.Data(), *observable, *sIdealNPdf, *bPdf);
		// termNPdf->setBufferFraction(2);

		// Set buffer fraction so tail not piles on the start
		terms->add(*termNPdf);

		TString nameC = TString::Format("coeff%d", n);
		TString titleC = TString::Format("Term %d coefficient", n);
		RooFormulaVar* coeffN = new RooFormulaVar(nameC.Data(), nameC.Data(), "exp(-@0)*@0^@1/TMath::Factorial(@1)", RooArgList(*(pars->mu),*nVar));

		// Last coeficient do not include. Root will automatically set it to 1-sum (N-1)
//		if (n != nTerms - 1) coefficients->add(*coeffN);
		coefficients->add(*coeffN);
	}

	// Sum terms of the real PM responce function
	// Create extended pdf: number of components is same as number of coefficients
	RooAddPdf* sRealPdf = new RooAddPdf("sRealPdf", "Real PM responce function", *terms, *coefficients);
	// sRealPdf->fixAddCoefNormalization(RooArgSet(*observable));

	// Prepare data histogram
	RooDataHist* data = new RooDataHist("data", "Dataset", RooArgList(*observable), hist);
	// RooDataHist* data = sRealPdf->generateBinned(*observable, 64000);

	RootUtils::startTimer();

	// Why pdf integration value is zero
	// RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
	// RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setRealValue("maxSteps", 30);
	// RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-6);
	// RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-6);

	// Perform fit
	// RooFitResult* fitResult = sRealPdf->fitTo(*data, RooFit::Save(kTRUE));
	RooFitResult* fitResult = sRealPdf->chi2FitTo(*data, RooFit::Save(kTRUE), RooFit::NumCPU(RootUtils::getNumCpu()), RooFit::Range(fitMin, xMax));

	// Chi2 fit - does not work because zero values
	// RooChi2Var* chi2 = new RooChi2Var("#chi^{2}", "chi square", *sRealPdf, *data, kTRUE, 0, 0, RootUtils::getNumCpu());
	// RooChi2Var* chi2 = new RooChi2Var("#chi^{2}", "chi square", *sRealPdf, *data);
	// RooMinimizer* m = new RooMinimizer(*chi2);
	// m->setMinimizerType("Minuit2");
	// Int_t resultMigrad = m->migrad();
	// Int_t resultHesse = m->hesse();
	// RooFitResult* fitResult = m->save();

	RootUtils::stopAndPrintTimer();

	// Create RooPlot from energy axis frame
	RooPlot* spectrumPlot = observable->frame();
	TString plotTitle = TString::Format("RooFit of %s", hist->GetTitle());
	spectrumPlot->SetTitle(plotTitle.Data());

	// Configure axis labels and look
	GraphicsUtils::styleAxis(spectrumPlot->GetXaxis(), "ADC channel", 1.2, 0.02, kTRUE); // Title, Title offset, Label offset
	GraphicsUtils::styleAxis(spectrumPlot->GetYaxis(), "Events", 1.1, 0.012, kTRUE);

	// Plot data points
	data->plotOn(spectrumPlot, RooFit::LineColor(kGray + 3), RooFit::MarkerSize(0.5), RooFit::Name("data"));
	sRealPdf->plotOn(spectrumPlot, RooFit::Name("fit"));

	// Plot model components
	for (UInt_t i = 0; i < terms->getSize(); i++){
		RooAbsPdf* pdf = (RooAbsPdf*)terms->at(i);
		if (pdf){
			sRealPdf->plotOn(spectrumPlot, RooFit::Components(*pdf), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
		}
	}

	// Print fit parameters
	sRealPdf->paramOn(spectrumPlot, RooFit::Layout(0.5, 0.9, 0.9));

	// Create canvas for drawing
	if (!pad){
		TString padName = TString::Format("canvas_%d", timestamp->Get());
		pad = new TCanvas(padName.Data());
	}
	pad->SetBottomMargin(0.1);

	// Draw the plot
	spectrumPlot->Draw();

	// Get chi^2 from the plot curve and historam and add it to pave
	RooCurve* curveFit = spectrumPlot->getCurve("fit");
	Chi2Struct chi2Struct = HistUtils::getChi2(hist, curveFit, sRealPdf);
	TString line = TString::Format("#chi^{2} =  %d / %d = %.2f", (Int_t)(chi2Struct.chiSum), chi2Struct.degreesOfFreedom, chi2Struct.chi2);
	GraphicsUtils::addLineToPave(pad, sRealPdf, line.Data());
}

void FitUtils::doFit(TH1* hist, FitParameters* pars, AbsComponentFunc* funcObject, Int_t fitMin, TVirtualPad* pad, Bool_t noTerm0){
	gSystem->Sleep(100);
	TDatime* timestamp = new TDatime();

	// Number of terms in the fit function
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;

	// Get list of ROOT parameters for single function
	RooArgList* parameters = pars->getList();

	// Instantiate fitting function
	// NOTE: IWill experience memory leaks if define fit function
	// inside fit function object class like this:
	// fitFunction = new TF1("fitFunction", this, &FuncSRealOld::func, xMin, xMax, nPar, "FuncSRealOld", "func");
	// Therefore we instantiate fit function outside of function object

	// Update: to save memory and easier access the fit components we introduce
	// AbsComponentFunction; it stores function components
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	TString funcName = TString::Format("func_%d", timestamp->Get());
	TF1* func = new TF1(funcName.Data(), funcObject, &AbsComponentFunc::func, xMin, xMax, parameters->getSize());

	// Set function starting parameter values, names and limits
	TIterator* it = parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			func->SetParName(i, parameter->GetName());
			func->SetParameter(i, parameter->getVal());
			func->SetParLimits(i, parameter->getMin(), parameter->getMax());
			// Double checking the parameter values
			std::cout << "Parameter " << i << ": " << parameter->GetName() << " " << parameter->getVal() << std::endl;
			i++;
		}
	}

	// Set function points along x axis (for plotting)
	func->SetNpx(1000);

	// Set default integrator - very important!
	// "GAUSS", "GAUSSLEGENDRE", "ADAPTIVE", "ADAPTIVESINGULAR", "NONADAPTIVE"
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("GAUSSLEGENDRE");

	// For FFT Integral
	// ROOT::Math::IntegratorOneDimOptions::SetDefaultNPoints(10000);
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

	if (!pad){
		TString padName = TString::Format("canvas_%d", timestamp->Get());
		pad = new TCanvas(padName.Data());
	}
	// canvas->SetLeftMargin(0.15);
	// canvas->SetRightMargin(0.05);


	// Perform fit
	RootUtils::startTimer();
	hist->Fit(func, "V", "", fitMin); // Add range here
	RootUtils::stopAndPrintTimer();

	// Display fit parameters and chi^2 in statistis box
	// https://root.cern.ch/doc/master/classTPaveStats.html#PS02
	GraphicsUtils::setStatsFitOption(hist, pad, 112);
	hist->Draw();
	func->Draw("SAME");

	// Obtain function fit parameters
	Int_t nFitPar = func->GetNpar();
	Double_t* fitParameters = new Double_t[nFitPar];
	func->GetParameters(fitParameters);

	// Print obtained parameters
	// std::cout << "Obtained parameters:" << std::endl;
	// for (UInt_t i=0; i < nFitPar; i++){
	// 	std::cout << "Parameter " << i << ": " << fitParameters[i] << std::endl;
	// }

	// Print histogram and fitting function integrals
	Double_t histIntegral = hist->Integral(xMin, xMax);
	Double_t funcIntegral = func->Integral(xMin, xMax);
	std::cout << "TH1 hist integral: " << histIntegral << std::endl;
	std::cout << "TF1 func integral: " << funcIntegral << std::endl;

	// Retrieve component functions
	TList* components = funcObject->getComponents();

	// Calculate component integrals (not normalized to hist integral) and total components integral
//	Double_t* componentIntegrals = new Double_t[nTerms];
//	Double_t allComponentsIntegral = 0;
//	for (UInt_t n=0; n<=components->LastIndex(); n++){
//		TF1* component = (TF1*)(components->At(n));
//		if (component){
//			if (component->GetNpar() == 2*nFitPar){
//				// If component is a convolution of two functions
//				Double_t* convParameters = getConvFitParameters(fitParameters, nFitPar);
//				component->SetParameters(convParameters);
//			}
//			else {
//				// If component is a regular function
//				component->SetParameters(fitParameters);
//			}
//			Double_t componentIntegral = component->Integral(xMin, xMax);
//			componentIntegrals[n] = componentIntegral;
//			allComponentsIntegral += componentIntegral;
//			std::cout << "Component " << n << " integral: " << componentIntegrals[n] << std::endl;
//		}
//	}
//	std::cout << "All components integral: " << allComponentsIntegral << std::endl;

	// Create and plot normalized component functions for every component
	for (UInt_t n=0; n<=components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
			// Component needs to be normalized to the number of the histogram events
			// and on the ratio of component integral to the all components integral ? lol just histogram events
			// Double_t ratio = componentIntegrals[n]/allComponentsIntegral;
			Double_t mu = fitParameters[6];		// number of photo-electrons
			Double_t coefficient = 0;

			// Account on the absence of the term 0
			if (noTerm0) {
				coefficient = pow(mu,n+1)*pow(TMath::E(),-mu)/TMath::Factorial(n+1);
				coefficient = coefficient / (1-pow(TMath::E(),-mu));
			}
			else {
				coefficient = pow(mu,n)*pow(TMath::E(),-mu)/TMath::Factorial(n);
			}

			TF1Normalize* normFunc = new TF1Normalize(component, coefficient*funcIntegral);
			TString fName = TString::Format("%s_norm", component->GetName());
			TF1* f;
			if (component->GetNpar() == 2*nFitPar){
				// If component is a convolution of two functions
				f = new TF1(fName.Data(), normFunc, &TF1Normalize::func, xMin, xMax, nFitPar*2, "TF1Normalize", "func");
				Double_t* convParameters = getConvFitParameters(fitParameters, nFitPar);
				f->SetParameters(convParameters);
			}
			else {
				// If component is a regular function
				f = new TF1(fName.Data(), normFunc, &TF1Normalize::func, xMin, xMax, nFitPar, "TF1Normalize", "func");
				f->SetParameters(fitParameters);
			}
			// f->SetParameters(fitParameters);
			f->SetLineStyle(ELineStyle::kDashed);
			f->SetNpx(200);
			f->Draw("SAME");
		} else {
			std::cout << "Error getting the component " << n << std::endl;
		}
	}

	GraphicsUtils::alignStats(hist, pad);
}

void FitUtils::fillHistogramFromFuncObject(TH1* hist, FitParameters* pars, AbsComponentFunc* funcObject){
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();

	// Get list of ROOT parameters for single function
	RooArgList* parameters = pars->getList();

	TF1* func = new TF1("func_fill", funcObject, &AbsComponentFunc::func, xMin, xMax, parameters->getSize());

	// Set function starting parameter values, names and limits
	TIterator* it = parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			func->SetParName(i, parameter->GetName());
			func->SetParameter(i, parameter->getVal());
			func->SetParLimits(i, parameter->getMin(), parameter->getMax());
			// Double checking the parameter values
			// std::cout << "Parameter " << i << ": " << parameter->GetName() << " " << parameter->getVal() << std::endl;
			i++;
		}
	}

	hist->SetBinContent(1, 64000);
	hist->FillRandom("func_fill", 64000);
	hist->SetBinContent(1, hist->GetBinContent(1)-64000);
}

// Sun terms like in ROOT documentation "term0+term1+...." - DOES NOT WORK
void FitUtils::doFitTest(TH1* hist, FitParameters* pars){
	// Get list of ROOT parameters for single function
	RooArgList* parameters = pars->getList();

	// Instantiate fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();

	// Components will contain individual fit function terms
	TList* components = new TList();

	// Term 0 is Pedestal and eponential background
	FuncTerm0* funcTerm0 = new FuncTerm0();
	TF1* term0 = new TF1("term0", funcTerm0, &FuncTerm0::func, xMin, xMax, parameters->getSize(), 1, TF1::EAddToList::kAdd);
	components->Add(term0);

	// Terms 1..N are gaussians convoluted with the background function
	Int_t nTerms = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n=1; n < nTerms; n++){
		FuncTermN* funcTermN = new FuncTermN(n);
		TString name = TString::Format("term%d", n);
		TF1* termN = new TF1(name.Data(), funcTermN, &FuncTermN::func, xMin, xMax, parameters->getSize());
		components->Add(termN);
	}

	// Generate composite fit function name "term0+term1+term..."
	// https://root.cern.ch/doc/master/classTF1.html#F4
	TString addName = term0->GetName();
	for (UInt_t n=1; n<=components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
			addName += "+";
			addName += component->GetName();
		}
	}
	std::cout << addName.Data() << std::endl;
	TF1 *fitFunction = new TF1("fitFunction", addName.Data());

	TF1Normalize* normFitObject = new TF1Normalize(fitFunction, hist->Integral());
	TF1 *normFitFunction = new TF1("normFitFuntion", normFitObject, &TF1Normalize::func, xMin, xMax, parameters->getSize(), 1, TF1::EAddToList::kAdd);

	// For each component set parameter names, values and limits
	TIterator* it = parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			normFitFunction->SetParName(i, parameter->GetName());
			normFitFunction->SetParameter(i, parameter->getVal());
			normFitFunction->SetParLimits(i, parameter->getMin(), parameter->getMax());
			i++;
		}
	}

	// Draw histogram
	TCanvas* canvas = new TCanvas("canvas", "testCanvas", 640, 512);
	hist->Draw();

	// Fit histogram
	// hist->Fit(func, "V");
	// GraphicsUtils::showFitParametersInStats(hist, canvas);

	fitFunction->Draw("SAME");
}

// Constructs array of parameters for convolution function
// If parameters [1,2,5] then convParameters [1,2,5,1,2,5] doubles the array
Double_t* FitUtils::getConvFitParameters(Double_t* parameters, Int_t nPar){
	Double_t* convParameters = new Double_t[nPar*2];
	for (UInt_t i = 0; i < nPar*2; i++){
		convParameters[i] = parameters[i%nPar];
	}
	return convParameters;
}
