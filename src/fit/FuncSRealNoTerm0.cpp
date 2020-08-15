/*
 * FuncSRealNoTerm0.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "FuncSRealNoTerm0.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include <TDatime.h>
#include "./components/FuncB.h"
#include "./components/FuncTerm0.h"
#include "./components/FuncTermN.h"


FuncSRealNoTerm0::FuncSRealNoTerm0(TH1* h, Int_t nParVal) : AbsComponentFunc(), hist(h), nPar(nParVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?
	TDatime* timestamp = new TDatime();

	// Instantiate terms of the real FuncSRealNoTerm0
	// Terms 0..N are background function covoluted wit the Ideal FuncSRealNoTerm0 function
	Int_t nMax = Constants::getInstance()->parameters.termsNumber;
	for (UInt_t n=1; n < nMax; n++){
		FuncTermN* funcTermN = new FuncTermN(n);
		TString termNName = TString::Format("term%d_%d", n, timestamp->Get());
		TF1* termN = new TF1(termNName.Data(), funcTermN, &FuncTermN::func, xMin, xMax, nPar, "FuncTermN", "func");
		components->Add(termN);
	}
}

FuncSRealNoTerm0::~FuncSRealNoTerm0() {
}

// Final fitting function - needs to be normalized
// Components from ./components do not need to be normalized
Double_t FuncSRealNoTerm0::func(Double_t* _x, Double_t* par) {
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
			value += component->EvalPar(_x, par);			// Sum the cumulated value
		    component->SetParameters(par);					// Set parameters
		    // Sum the total integral
			integral += component->Integral(xMin, xMax, 1E-6);
		} else {
			std::cout << "Error getting the component" << std::endl;
		}
	}

	// Return normalized function value
	return value/integral*(hist->Integral());
}