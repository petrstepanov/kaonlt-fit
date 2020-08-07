/*
 * FitUtils.cpp
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#include <iostream>
#include <TF1Convolution.h>
#include <RooRealVar.h>
#include "FitUtils.h"

#include "../fit/SpectrumSimplified.h"
#include "../fit/SpectrumReal.h"
#include "../model/Constants.h"

FitUtils::FitUtils() {
}

FitUtils::~FitUtils() {
}

TF1* FitUtils::getRealFitFunction(TH1* hist){
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();

	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	Int_t termsNumber = 20; //Constants::getInstance()->parameters.termsNumber;
	SpectrumSimplified* spectrum = new SpectrumSimplified(hist->Integral(), xMin, xMax, termsNumber);
	TF1* realFunc = new TF1("realFunc", spectrum, &SpectrumSimplified::func, xMin, xMax, SpectrumSimplified::parameters->getSize(), "Spectrum", "func");

	// Iterate parameters, set their names, starting values and limits
	TIterator* it = SpectrumSimplified::parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			realFunc->SetParName(i, parameter->GetName());
			realFunc->SetParameter(i, parameter->getVal());
			realFunc->SetParLimits(i, parameter->getMin(), parameter->getMax());

			// Fix Pedestal
			// if (strcmp(parameter->GetName(),"Q0")==0){
			// 	Double_t pedestal = hist->GetBinCenter(hist->GetMaximumBin());
			// 	realFunc->FixParameter(i, pedestal);
			// }

			// Fix w = 0
			// if (strcmp(parameter->GetName(),"w")==0){
			//  realFunc->FixParameter(i, 0.383);
			// }

			i++;
		}
	}


	// Set the number of points used to draw the fit function
	realFunc->SetNpx(1000);

	return realFunc;
}
