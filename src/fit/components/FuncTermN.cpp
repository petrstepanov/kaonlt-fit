/*
 * FuncTermN.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FuncTermN.h"
#include "../../utils/MathematicaAliases.h"
#include "../../model/Constants.h"

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

	// Solution for oscillations: manually cut everything (-infty, mean-2*sigma
	Double_t mean = Q0 + n*Q1;
	Double_t sigma = sqrt((Power(s0,2) + n*Power(s1,2)));
	Double_t fwhm = sigma*Constants::SIGMA_TO_FWHM;

	if (x < mean - fwhm*2){
		return 0;
	}

	// Calculate function value
	Double_t y = _x[0];
	Double_t value = // begin mathematica code from "/mathematica/termN.nb"
// With coefficients:
//			(Power(mu,n)*((1 - w)/
//			        (Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*
//			          Sqrt(n)*Sqrt(2*Pi)*s1) +
//			       (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/
//			              (Sqrt(2)*Sqrt(n)*s1)) +
//			            Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/
//			               (Sqrt(2)*Sqrt(n)*s1))*
//			             Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
//			        (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))))/
//			   (Power(E,mu)*Factorial(n))

// Without coefficient from Paper (wrong components normalization)
//			(1 - w)/(Power(E,Power(-Q0 - n*Q1 + x,2)/(2.*n*Power(s1,2)))*Sqrt(n)*Sqrt(2*Pi)*s1) +
//			   (a*w*(Erf(Abs(-(n*Q1) - a*n*Power(s1,2))/(Sqrt(2)*Sqrt(n)*s1)) +
//			        Erf(Abs(-Q0 - n*Q1 - a*n*Power(s1,2) + x)/(Sqrt(2)*Sqrt(n)*s1))*Sign(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))/
//			    (2.*Power(E,a*(-Q0 - n*Q1 - a*n*Power(s1,2) + x)))

// With Coefficient from Mathematica convolution
			((1 - w)/(Power(E,Power(Q0 + n*Q1 - y,2)/(2.*(Power(s0,2) + n*Power(s1,2))))*s0*Sqrt(Power(s0,-2) + 1/(n*Power(s1,2)))) +
			     (a*Power(E,(a*(2*Q0 + 2*n*Q1 + a*n*Power(s1,2) - 2*y))/2.)*Sqrt(Pi/2.)*w*(1 - Erf((Sqrt(1/(n*Power(s1,2)))*(n*(Q1 + a*Power(s1,2)) - y))/Sqrt(2)) -
			          (Sqrt(Power(s1,-2))*(Q0 + n*(Q1 + a*Power(s1,2)) - y)*Erf(Sqrt(Power(Q0 + n*(Q1 + a*Power(s1,2)) - y,2)/(n*Power(s1,2)))/Sqrt(2)))/Sqrt(Power(Q0 + n*(Q1 + a*Power(s1,2)) - y,2)/Power(s1,2)) +
			          (Sqrt(Power(s1,-2))*(n*(Q1 + a*Power(s1,2)) - y)*Erf(Sqrt(Power(-(n*(Q1 + a*Power(s1,2))) + y,2)/(n*Power(s1,2)))/Sqrt(2)))/Sqrt(Power(-(n*(Q1 + a*Power(s1,2))) + y,2)/Power(s1,2))))/
			      Sqrt(1/(n*Power(s1,2))))/(Sqrt(n)*Sqrt(2*Pi)*s1)

// Split analytical convolution result in two terms
//			(1 - w)/(Power(E,Power(Q0 + n*Q1 - y,2)/(2.*(Power(s0,2) + n*Power(s1,2))))*Sqrt(2*Pi)*Sqrt(Power(s0,2) + n*Power(s1,2)))
//			+
//			(a*Power(E,(a*(2*Q0 + 2*n*Q1 + a*n*Power(s1,2) - 2*y))/2.)*w*(1 - Erf((Sqrt(n/Power(s1,2))*(Q1 + a*Power(s1,2)))/Sqrt(2)) +
//			       (Sqrt(Power(s1,-2))*(Q1 + a*Power(s1,2))*Erf(Sqrt((n*Power(Q1 + a*Power(s1,2),2))/Power(s1,2))/Sqrt(2)))/Sqrt(Power(Q1 + a*Power(s1,2),2)/Power(s1,2)) -
//			       (Sqrt(Power(s1,-2))*(Q0 + n*(Q1 + a*Power(s1,2)) - y)*Erf(Sqrt(Power(Q0 + n*(Q1 + a*Power(s1,2)) - y,2)/(n*Power(s1,2)))/Sqrt(2)))/Sqrt(Power(Q0 + n*(Q1 + a*Power(s1,2)) - y,2)/Power(s1,2))))/
//			   (2.*Sqrt(n)*Sqrt(1/(n*Power(s1,2)))*s1)
	; // end mathematica code

	return value < 0 ? 0 : value;
}

Double_t FuncTermN::getIntegral(Double_t xMin, Double_t xMax, Double_t* par){
	return 0;
}
