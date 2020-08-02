/*
 * Spectrum.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "Spectrum.h"
#include "../model/Constants.h"
#include <TMath.h>

Spectrum::Spectrum(Int_t nMaxVal=100) : nMax(nMaxVal), pi(TMath::Pi()), e(TMath::E()) {
	// Initialize parameters as RooRealVars even though we're not using RooFit
	// Convenient because RooRealVar has name, value and limits
	// Parameter values taken from Fig.2, https://doi.org/10.1016/0168-9002(94)90183-X
	RooRealVar* Q0 = new RooRealVar("Q0", "pedestal", 23.26, 0, Constants::CH_MAX, "e");
	RooRealVar* s0 = new RooRealVar("s0", "standard deviation of the type I background process", 0.192, 0, 1, "");
	RooRealVar* Q1 = new RooRealVar("Q1", "average charge at the PM output", 35.04, 0, 500, "e");
	RooRealVar* s1 = new RooRealVar("s1", "corresponding standard deviation of the charge distribution", 11.73, 0, 100, "");
	RooRealVar* w  = new RooRealVar("w",  "probability that signal is accompanied by type II background process", 0.383, 0, 1, "");
	RooRealVar* a  = new RooRealVar("a",  "coefficient of the exponential decrease of the type II background", 0.034, 0, 0.1, "");
	RooRealVar* mu = new RooRealVar("mu", "number of photo-electrons", 1.68, 0, 50, "");
	parameters->add(*Q0);
	parameters->add(*s0);
	parameters->add(*Q1);
	parameters->add(*s1);
	parameters->add(*w);
	parameters->add(*a);
	parameters->add(*mu);
}

Spectrum::~Spectrum() {
}

RooArgList* Spectrum::parameters = new RooArgList();

Double_t Spectrum::ideal(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t mu = par[0]; // number of photo-electrons
	Double_t Q1 = par[1]; // average charge at the PM output
	Double_t s1 = par[2]; // corresponding standard deviation of the charge distribution

	Double_t sum = 0;

	for (Int_t n = 0; n <= nMax; n++){
		Double_t frac1 = pow(mu, 0.)*pow(e,-mu)/TMath::Factorial(n);
		Double_t frac2 = 1/s1/sqrt(2*pi*n);
		Double_t frac3 = exp(-pow(x-n*Q1,2)/(2*n*s1*s1));
		sum += frac1*frac2*frac3;
	}
	return sum;
}

Double_t Spectrum::background(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t w = par[0];  // probability that signal is accompanied by type II background process
	Double_t s0 = par[1]; // standard deviation of the type I background process
	Double_t a = par[2];  // coefficient of the exponential decrease of the type II background


	Double_t bg = (1-w)/s0/sqrt(2*pi)*exp(-x*x/(2*s0*s0));
	if (x >= 0){
		bg += w*a*exp(-a*x);
	}
	return bg;
}

Double_t Spectrum::real(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// TODO: Account on the channel ratio
	// In paper ~500 channels, we have ~20000

	// Constants
	Double_t e = TMath::E();
	Double_t pi = TMath::Pi();

	// Helper variables
	Double_t theta = (x < 0)? 0 : 1;
	Double_t Qsh = w/a;

	if (x < 0) return 0;

	Double_t sum = 0;

	// First term
	sum += ((1-w)/s0/sqrt(2*pi)*exp(-(x-Q0)*(x-Q0)/2/s0/s0)+w*theta*(x-Q0)*a*exp(-a*(x-Q0)))*exp(-mu);

	// Other terms
	for (Int_t n = 1; n <= nMax; n++){
		Double_t frac1 = pow(mu, n)*exp(-mu)/TMath::Factorial(n);
		Double_t frac2 = 1/s1/sqrt(2*pi*n);
		Double_t frac3 = exp(-pow(x-Q0-Qsh-n*Q1,2)/(2*n*s1*s1));
		sum += frac1*frac2*frac3;
	}

	// std::cout << x << "\t" << sum << std::endl;
	return sum;
}

