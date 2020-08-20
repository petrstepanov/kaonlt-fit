/*
 * parameters.cpp
 *
 *  Created on: Aug 16, 2020
 *      Author: petrstepanov
 */

#include "FitParameters.h"
#include "../model/Constants.h"

FitParameters::FitParameters(ParametersType type) {
	// Instantiate initial fit parameter vaues
	parameters = new RooArgList();
	if (type == ParametersType::forBellamyHist){
		// For Bellamy spectrum fit
		RooRealVar* Q0 = new RooRealVar("Q_{0}", "pedestal", 23.26, 10., 40., "");
		RooRealVar* s0 = new RooRealVar("#sigma_{0}", "standard deviation of the type I background process", 0.192, 0., 0.3, ""); // ->10
		RooRealVar* Q1 = new RooRealVar("Q_{1}", "average charge at the PM output", 35.04, 15., 50., "");
		RooRealVar* s1 = new RooRealVar("#sigma_{1}", "corresponding standard deviation of the charge distribution", 11.73, 0., 20., ""); // ->100
		RooRealVar* w  = new RooRealVar("w", "probability that signal is accompanied by type II background process", 0.383, 0., 1., "");
		RooRealVar* a  = new RooRealVar("#alpha", "coefficient of the exponential decrease of the type II background", 0.034, 0., 0.1, ""); // ->10
		RooRealVar* mu = new RooRealVar("#mu", "number of photo-electrons", 1.68, 1, 5, "");  // -> 20
		parameters->add(*Q0);
		parameters->add(*s0);
		parameters->add(*Q1);
		parameters->add(*s1);
		parameters->add(*w);
		parameters->add(*a);
		parameters->add(*mu);
	} else {
		// for KaonLT Prototype spectra fit - read parameters from file
		const char* fileName = Constants::getInstance()->parameters.fitParamsFileName.Data();
		parameters = readParametersFromFile(fileName);
	}
}

FitParameters::~FitParameters() {
}

Double_t* FitParameters::getArray(){
	Double_t* array = new Double_t(parameters->getSize());
	for (UInt_t i = 0; i < parameters->getSize(); i++){
		 RooRealVar* parameter = (RooRealVar*)parameters->at(i);
		 array[i] = parameter->getVal();
	}
	return array;
}

RooArgList* FitParameters::getList(){
	return parameters;
}

RooArgList* FitParameters::readParametersFromFile(const char* filename){
	RooArgList* params = new RooArgList();
	FILE * pFile;
	pFile = fopen(filename, "r");
	if (pFile == NULL) {
		std::cout << "\"" << filename << "\" file not found." << std::endl;
		return params;
	}
	char* name = new char[128];
	char* description = new char[128];
	char* type = new char[128];
	Double_t val, min, max, error;

	// Skip header
	char buffer[256];
	if (fgets(buffer, 256, pFile) == NULL) return params;

	// Read parameters
	// Scanf with spaces. https://stackoverflow.com/questions/2854488/reading-a-string-with-spaces-with-sscanf
	while (fscanf(pFile, "%s\t%lf\t%lf\t%lf\t%s\t%[^\n]s", name, &val, &min, &max, type, description) != EOF) {
		RooRealVar* parameter = new RooRealVar(name, description, val, min, max);
		if (strcmp(type, "fixed") == 0) {
			parameter->setConstant(kTRUE);
		}
		params->add(*parameter);
	}
	fclose(pFile);

	// Print imported parameters
	std::cout << "\nImported " << params->getSize() << " parameters from \"" << filename << "\":" << std::endl;
	// params->Print("V");
	 for (UInt_t i = 0; i < params->getSize(); i++){
		RooRealVar* par = (RooRealVar*) params->at(i);
		if (par){
			par->Print();
		}
	 }
	return params;
}
