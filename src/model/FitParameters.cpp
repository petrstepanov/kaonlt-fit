/*
 * parameters.cpp
 *
 *  Created on: Aug 16, 2020
 *      Author: petrstepanov
 */

#include "FitParameters.h"

FitParameters::FitParameters(ParametersType type) {
	// Instantiate parameters depending on the type of fit (Bellamy vs Kaon)
	if (type == ParametersType::forBellamyHist){
		Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10, 40, "e");
		s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0, 1, ""); // ->10
		Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 0, 100, "e");
		s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 0, 50, ""); // ->100
		w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.4, 0., 1., "");
		a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0, 1, ""); // ->10
		mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 0, 10, "");  // -> 20
	} else {
		Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10, 40, "e");
		s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0, 10, "");
		Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 0, 100, "e");
		s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 0, 100, "");
		w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.4, 0., 1., "");
		a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0, 10, "");
		mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 0, 20, "");
	}
	// Fill list with parameters
	parameters = new RooArgList();
	parameters->add(*Q0);
	parameters->add(*s0);
	parameters->add(*Q1);
	parameters->add(*s1);
	parameters->add(*w);
	parameters->add(*a);
	parameters->add(*mu);

}

FitParameters::~FitParameters() {
}

Double_t* FitParameters::getArray(){
	Double_t* array = new Double_t(parameters->size());
	for (UInt_t i = 0; i < parameters->size(); i++){
		 RooRealVar* parameter = (RooRealVar*)parameters->at(i);
		 array[i] = parameter->getVal();
	}
	return array;
}

RooArgList* FitParameters::getList(){
	return parameters;
}
