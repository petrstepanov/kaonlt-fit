/*
 * Spectrum.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include "Spectrum.h"
#include "../model/Constants.h"
#include <TMath.h>

Spectrum::Spectrum(Double_t histIntegralVal, Int_t xMinVal, Int_t xMaxVal, Int_t nMaxVal) :
	nMax(nMaxVal), xMin(xMinVal), xMax(xMaxVal), histIntegral(histIntegralVal), pi(TMath::Pi()), e(TMath::E()) {
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

//Double_t Spectrum::ideal(Double_t* _x, Double_t* par) {
//	Double_t x = _x[0];
//
//	// Parameters:
//	Double_t mu = par[0]; // number of photo-electrons
//	Double_t Q1 = par[1]; // average charge at the PM output
//	Double_t s1 = par[2]; // corresponding standard deviation of the charge distribution
//
//	Double_t sum = 0;
//
//	for (Int_t n = 0; n <= nMax; n++){
//		Double_t frac1 = pow(mu, 0.)*pow(e,-mu)/TMath::Factorial(n);
//		Double_t frac2 = 1/s1/sqrt(2*pi*n);
//		Double_t frac3 = exp(-pow(x-n*Q1,2)/(2*n*s1*s1));
//		sum += frac1*frac2*frac3;
//	}
//	return sum;
//}
//
//Double_t Spectrum::background(Double_t* _x, Double_t* par) {
//	Double_t x = _x[0];
//
//	// Parameters:
//	Double_t w = par[0];  // probability that signal is accompanied by type II background process
//	Double_t s0 = par[1]; // standard deviation of the type I background process
//	Double_t a = par[2];  // coefficient of the exponential decrease of the type II background
//
//
//	Double_t bg = (1-w)/s0/sqrt(2*pi)*exp(-x*x/(2*s0*s0));
//	if (x >= 0){
//		bg += w*a*exp(-a*x);
//	}
//	return bg;
//}

// Alias functions for the Mathematica cform[%] command
Double_t Sqrt(Double_t x){
	return sqrt(x);
}

Double_t Power(Double_t x, Double_t y){
	return pow(x,y);
}

Double_t Factorial(Int_t n){
	return TMath::Factorial(n);
}

Int_t UnitStep(Double_t x){
	return (x<0)?0:1;
}

Double_t Erf(Double_t x){
	return TMath::Erf(x);
}

// Constants
Double_t E = TMath::E();
Double_t Pi = TMath::Pi();

// TH1::Fit - fitting function should be normalized
// https://root-forum.cern.ch/t/root-fit-unbindata-example-is-not-working/28462

Double_t Spectrum::realIndefInt(Double_t x, Double_t* par) {

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Calculate integral
	Double_t integral = 0;

	// First term
	integral += // begin mathematica code from "/mathematica/term1.nb"
			(((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2. +
			     (w - Power(E,a*Q0 - a*x)*w)*UnitStep(-Q0 + x))/Power(E,mu)
	; // end mathematica code

	// Other terms
	for (Int_t n = 1; n <= nMax; n++){
		integral += // begin mathematica code from "/mathematica/term2.nb"
				-(Power(mu,n)*Erf((w + a*(Q0 + n*Q1 - x))/(Sqrt(2)*a*Sqrt(n)*s1)))/
				   (2.*Power(e,mu)*Factorial(n))
		; // end mathematica code
	}

	return integral;
}

Double_t Spectrum::realDefInt(Double_t* par){
	return realIndefInt(xMax, par) - realIndefInt(xMin, par);
}

Double_t Spectrum::realDefIntSimple(Double_t* par){
	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t integral = 0;

	for (Int_t i = xMin; i < xMax; i++){
		Double_t x = i+0.5;
		integral += // begin mathematica code from "/mathematica/term2.nb"
				((1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) +
				     (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x)))/Power(E,mu)
		; // end mathematica code

		// Other terms
		for (Int_t n = 1; n <= nMax; n++){
			integral += // begin mathematica code from "/mathematica/term2.nb"
					Power(mu,n)/(Power(e,mu)*Power(E,
					      Power(-Q0 - n*Q1 - w/a + x,2)/(2.*n*Power(s1,2)))*Sqrt(n)*
					     Sqrt(2*Pi)*s1*Factorial(n))
			; // end mathematica code
		}
	}
	return integral;
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

	// Helper variables
	// Double_t theta = (x < 0)? 0 : 1;
	Double_t Qsh = w/a;

	// if (x < 0) return 0;

	Double_t sum = 0;

	// First term
	sum +=  // begin mathematica code from "/mathematica/term2.nb"
			((1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) +
			     (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x)))/Power(E,mu)
	; // end mathematica code

	// Other terms
	for (Int_t n = 1; n <= nMax; n++){
		sum += // begin mathematica code from "/mathematica/term2.nb"
				Power(mu,n)/(Power(e,mu)*Power(E,
				      Power(-Q0 - n*Q1 - w/a + x,2)/(2.*n*Power(s1,2)))*Sqrt(n)*
				     Sqrt(2*Pi)*s1*Factorial(n))
		; // end mathematica code
	}

	Double_t defIntegral = realDefIntSimple(par); //realDefInt(par);
	return sum/defIntegral*histIntegral;
}

