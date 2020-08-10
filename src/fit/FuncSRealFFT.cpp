/*
 * FuncSRealFFT.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "FuncSRealFFT.h"
#include "../model/Constants.h"
#include "../utils/MathematicaAliases.h"
#include <TF1Convolution.h>
#include <TMath.h>
#include "./components/FuncB.h"
#include "./components/FuncSIdealN.h"
#include "./components/FuncTerm0.h"

FuncSRealFFT::FuncSRealFFT(TH1* h, Int_t nMaxVal, Int_t nParVal) : AbsComponentFunc(), hist(h), nMax(nMaxVal), nPar(nParVal) {
	// Init TF1 finctions used to cunstruct the final fitting function
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	// Since fitting functions are defined in the same class, we are passing this pointer
	// TODO: is this ok that we are passing more variables than needed for bg and termN?

	// Instantiate terms of the real FuncSRealFFT
	// Zero term has an uncertainty. Its approximate value is taken from (10)
	FuncTerm0* funcTerm0 = new FuncTerm0();
	TF1* term0 = new TF1("term0", funcTerm0, &FuncTerm0::func, xMin, xMax, nPar, "FuncTerm0", "func");
	components->Add(term0);

	// Terms 1..N are background function covoluted wit the Ideal FuncSRealFFT function
	FuncB* funcB = new FuncB();
	TF1* b = new TF1("b", funcB, &FuncB::func, xMin, xMax, nPar, "FuncB", "func");
	for (UInt_t n=1; n < nMax; n++){
		FuncSIdealN* funcSIdealN = new FuncSIdealN(n);
		TString name = TString::Format("SIdeal%d", n);
		TF1* SIdealN = new TF1(name.Data(), funcSIdealN, &FuncSIdealN::func, xMin, xMax, nPar, "FuncSIdealN", "func");

		TF1Convolution* conv = new TF1Convolution(SIdealN, b, xMin, xMax);
		conv->SetNofPointsFFT(1024);
		TString termName = TString::Format("term%d", n);
		TF1 *termN = new TF1(termName.Data(),*conv, xMin, xMax, conv->GetNpar());

		components->Add(termN);
	}
}

FuncSRealFFT::~FuncSRealFFT() {
}

Double_t FuncSRealFFT::func(Double_t* _x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t parForConvolution[] = {Q0, s0, Q1, s1, w, a, mu, Q0, s0, Q1, s1, w, a, mu};

	// Set component parameters

	// Loop over components
	Double_t value = 0;
	Double_t integral = 0;
	Int_t xMin = hist->GetXaxis()->GetXmin();
	Int_t xMax = hist->GetXaxis()->GetXmax();

	for (UInt_t n = 0; n <= components->LastIndex(); n++){
		TF1* component = (TF1*)(components->At(n));
		if (component){
			// Set parameters
		    if (n==0) component->SetParameters(par);
		    else component->SetParameters(parForConvolution);

		    // Sum the cumulated value
			if (n==0) value += component->EvalPar(_x, par);
			else value += component->EvalPar(_x, parForConvolution);

			// Sum the total integral
			integral += component->Integral(xMin, xMax);
		} else {
			std::cout << "Error getting the component" << std::endl;
		}
	}

	// Return normalized function value
	return value/integral*(hist->Integral());
}
