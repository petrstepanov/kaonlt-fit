/*
 * FitUtils.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FitUtils.h"
#include "../fit/FuncSReal.h"
#include "../fit/FuncSRealFFT.h"
#include <RooRealVar.h>
#include <TF1.h>


FitUtils::FitUtils() {
}

FitUtils::~FitUtils() {
}

TF1* FitUtils::getFuncSReal(TH1* hist, Int_t nMax, Bool_t isFFT){
	// Initialize parameters as RooRealVars even though we're not using RooFit
	// Convenient because RooRealVar has name, value and limits
	// Parameter values taken from Fig.2, https://doi.org/10.1016/0168-9002(94)90183-X
	RooRealVar* Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10, 40, "e");
	RooRealVar* s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0.1, 10, "");
	RooRealVar* Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 0, 100, "e");
	RooRealVar* s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 5, 50, "");
	RooRealVar* w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.4, 0.1, 1, "");
	RooRealVar* a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0, 0.1, "");
	RooRealVar* mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 0, 20, "");
	// Add parameters twice, each set for each convoluted function

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
