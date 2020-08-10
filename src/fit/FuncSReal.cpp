/*
 * FuncSReal.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "FuncSReal.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include "./components/FuncB.h"
#include "./components/FuncTerm0.h"
#include "./components/FuncTermN.h"


FuncSReal::FuncSReal(TH1* h, Int_t nMaxVal) : AbsComponentFunc(), hist(h), nMax(nMaxVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?

	// Instantiate terms of the real FuncSReal
	// Zero term has an uncertainty. Its approximate value is taken from (10)
	FuncTerm0* funcTerm0 = new FuncTerm0();
	TF1* term0 = new TF1("term0", funcTerm0, &FuncTerm0::func, xMin, xMax, nMax, "FuncTerm0", "func");
	components->Add(term0);

	// Terms 1..N are background function covoluted wit the Ideal FuncSReal function
	FuncB* funcB = new FuncB();
	TF1* b = new TF1("b", funcB, &FuncB::func, xMin, xMax, nMax, "FuncB", "func");
	for (UInt_t n=1; n < nMax; n++){
		FuncTermN* funcTermN = new FuncTermN(n);
		TString name = TString::Format("term%d", n);
		TF1* termN = new TF1(name.Data(), funcTermN, &FuncTermN::func, xMin, xMax, nMax, "FuncTermN", "func");
		components->Add(termN);
	}
}

FuncSReal::~FuncSReal() {
}

// Final fitting function - needs to be normalized
// Components from ./components do not need to be normalized
Double_t FuncSReal::func(Double_t* _x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Loop over components
	Double_t value = 0;
	Double_t integral = 0;
	Int_t xMin = hist->GetXaxis()->GetXmin();
	Int_t xMax = hist->GetXaxis()->GetXmax();

	for (Int_t n = 0; n <= components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
		    component->SetParameters(par);					// Set parameters
			value += component->EvalPar(_x, par);			// Sum the cumulated value
			integral += component->Integral(xMin, xMax);	// Sum the total integral
		} else {
			std::cout << "Error getting the component" << std::endl;
		}
	}

	// Return normalized function value
	return value/integral*(hist->Integral());
}
