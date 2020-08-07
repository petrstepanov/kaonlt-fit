/*
 * FuncTermN.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FuncTermN.h"
#include "../utils/MathematicaAliases.h"

FuncTermN::FuncTermN(Int_t nVal) : n(nVal) {
	// TODO Auto-generated constructor stub

}

FuncTermN::~FuncTermN() {
	// TODO Auto-generated destructor stub
}

Double_t FuncTermN::func(Double_t* _x, Double_t* par) {
	Double_t x = _x[0];

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Calculate function value
	Double_t value = // begin mathematica code from "/mathematica/term0.nb"
			(Power(mu,n)*((1 - w)/
			        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
			          Sqrt(n)*Sqrt(2*Pi)*s1) +
			       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
			              (Sqrt(2)*Sqrt(n)*s1)) +
			            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
			               (Sqrt(2)*Sqrt(n)*s1))*
			             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
			        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
			   (Power(E,mu)*Factorial(n))
	; // end mathematica code

	return value;
}

Double_t FuncTermN::getIntegral(Double_t xMin, Double_t xMax, Double_t* par){
	// Implementation of the Simpson's rule

	// Parameters:
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	// Newton-Leibniz formula
	Double_t integral = 0;
	for (UInt_t x = xMin+0.5; x <= xMax; x++){
		integral += // begin mathematica code from "/mathematica/term0.nb"
				(Power(mu,n)*((1 - w)/
				        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
				          Sqrt(n)*Sqrt(2*Pi)*s1) +
				       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
				              (Sqrt(2)*Sqrt(n)*s1)) +
				            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
				               (Sqrt(2)*Sqrt(n)*s1))*
				             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
				        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
				   (Power(E,mu)*Factorial(n))
		; // end mathematica code
	}

	return integral;
}
