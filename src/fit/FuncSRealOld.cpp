/*
 * FuncSRealOld.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include "FuncB.h"
#include "FuncSIdealN.h"
#include "FuncSRealOld.h"
#include "FuncTerm0.h"
#include "FuncTermN.h"

FuncSRealOld::FuncSRealOld(TH1* h, Int_t nMaxVal) : hist(h), nMax(nMaxVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	Int_t nPar = parameters->getSize();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?

	// Instantiate terms of the real FuncSRealOld
	// Zero term has an uncertainty. Its approximate value is taken from (10)
	FuncTerm0* funcTerm0 = new FuncTerm0();
	TF1* term0 = new TF1("term0", funcTerm0, &FuncTerm0::func, xMin, xMax, nPar, "FuncTerm0", "func");
	terms.push_back(term0);

	// Terms 1..N are background function covoluted wit the Ideal FuncSRealOld function
	FuncB* funcB = new FuncB();
	TF1* b = new TF1("b", funcB, &FuncB::func, xMin, xMax, nPar, "FuncB", "func");
	for (UInt_t n=1; n <= 1; n++){
		FuncTermN* funcTermN = new FuncTermN(n);
		TString name = TString::Format("term%d", n);
		TF1* term = new TF1(name.Data(), funcTermN, &FuncTermN::func, xMin, xMax, nPar, "FuncTermN", "func");
		terms.push_back(term);
	}

	// Instantiate fitting function
	fitFunction = new TF1("fitFunction", this, &FuncSRealOld::func, xMin, xMax, nPar, "FuncSRealOld", "func");

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
	parameters = new RooArgList();
	parameters->add(*Q0);
	parameters->add(*s0);
	parameters->add(*Q1);
	parameters->add(*s1);
	parameters->add(*w);
	parameters->add(*a);
	parameters->add(*mu);

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

	fitFunction->SetNpx(10000);
}

FuncSRealOld::~FuncSRealOld() {
}

Double_t FuncSRealOld::func(Double_t* _x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Sum terms
	Double_t sum = 0;
	for (TF1* func : terms) sum += func->EvalPar(_x,par);

	// Calculate integral
	Double_t integral = 0;
	Int_t xMin = hist->GetXaxis()->GetXmin();
	Int_t xMax = hist->GetXaxis()->GetXmax();

	// Create doubled parameters array for convoluted function
	for (TF1* func : terms){
		func->SetParameters(par);
		integral += func->Integral(xMin, xMax, 1);
	}

	// Return normalized function value
	return sum/integral*(hist->Integral());
}

TF1* FuncSRealOld::getFitFunction(){
	return fitFunction;
}
