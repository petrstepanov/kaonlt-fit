/*
 * FuncTerm0.cpp
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#include "FuncTerm0.h"
#include "../utils/MathematicaAliases.h"

FuncTerm0::FuncTerm0() {
	// TODO Auto-generated constructor stub

}

FuncTerm0::~FuncTerm0() {
	// TODO Auto-generated destructor stub
}

Double_t FuncTerm0::func(Double_t* _x, Double_t* par) {
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
			((1 - w)/(Power(E,Power(-Q0 + x,2)/(2.*Power(s0,2)))*Sqrt(2*Pi)*s0) +
			     (a*w*UnitStep(-Q0 + x))/Power(E,a*(-Q0 + x)))/Power(E,mu)
	; // end mathematica code

	return value;
}

Double_t FuncTerm0::getIntegral(Double_t xMin, Double_t xMax, Double_t* par){
	// Newton-Leibniz formula
	return indefiniteIntegral(xMax, par) - indefiniteIntegral(xMin, par);
}

Double_t FuncTerm0::indefiniteIntegral(Double_t x, Double_t* par) {
	// Parameters
	Double_t Q0 = par[0];		// average charge at the PM output
	Double_t s0 = par[1];		// standard deviation of the type I background process
	Double_t Q1 = par[2];		// average charge at the PM output
	Double_t s1 = par[3];		// corresponding standard deviation of the charge distribution
	Double_t w  = par[4];		// probability that signal is accompanied by type II background process
	Double_t a  = par[5];		// coefficient of the exponential decrease of the type II background
	Double_t mu = par[6];		// number of photo-electrons

	Double_t value =  // begin mathematica code from "/mathematica/term0.nb"
			(((-1 + w)*Erf((Q0 - x)/(Sqrt(2)*s0)))/2. +
			     (w - Power(E,a*Q0 - a*x)*w)*UnitStep(-Q0 + x))/Power(E,mu)
	; // end mathematica code

	return value;
}
