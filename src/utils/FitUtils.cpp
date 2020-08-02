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
#include "../fit/Spectrum.h"

FitUtils::FitUtils() {
	// TODO Auto-generated constructor stub

}

FitUtils::~FitUtils() {
	// TODO Auto-generated destructor stub
}

TF1* FitUtils::getConvFitFunction(Double_t xMin, Double_t xMax){
	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	Spectrum* spectrum = new Spectrum(10);
	TF1* idealFunc = new TF1("idealFunc", spectrum, &Spectrum::ideal, xMin, xMax, 3, "Spectrum", "ideal");
	TF1* bgFunc = new TF1("bgFunc", spectrum, &Spectrum::background, xMin, xMax, 3, "Spectrum", "background");

	TF1Convolution* conv = new TF1Convolution("idealFunc", "bgFunc", xMin, xMax);
	conv->SetNofPointsFFT(1024);

	TF1 *convFunc = new TF1("convFunc",*conv, xMin, xMax, conv->GetNpar());
	{
		// Iterate parameters, set their names, starting values and limits
		TIterator* it = Spectrum::parameters->createIterator();
		TObject* tempObj = 0;
		Int_t i = 0;
		while((tempObj=it->Next())){
			RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
			if(parameter){
				convFunc->SetParName(i, parameter->GetName());
				convFunc->SetParameter(i, parameter->getVal());
				convFunc->SetParLimits(i, parameter->getMin(), parameter->getMax());
				i++;
			}
		}
	}
	return convFunc;
}

TF1* FitUtils::getRealFitFunction(TH1* hist){
	Double_t xMin = hist->GetXaxis()->GetXmin();
	Double_t xMax = hist->GetXaxis()->GetXmax();

	// Instantiate TF1 from a member function of a general C++ class
	// https://root.cern.ch/doc/master/classTF1.html#F6
	Spectrum* spectrum = new Spectrum(20);
	TF1* realFunc = new TF1("realFunc", spectrum, &Spectrum::real, xMin, 2000, Spectrum::parameters->getSize(), "Spectrum", "ideal");

	// Iterate parameters, set their names, starting values and limits
	TIterator* it = Spectrum::parameters->createIterator();
	TObject* tempObj = 0;
	Int_t i = 0;
	while((tempObj=it->Next())){
		RooRealVar* parameter = dynamic_cast<RooRealVar*>(tempObj);
		if(parameter){
			realFunc->SetParName(i, parameter->GetName());
			realFunc->SetParameter(i, parameter->getVal());
			// realFunc->SetParLimits(i, parameter->getMin(), parameter->getMax());

			// Fix Pedestal
			// if (strcmp(parameter->GetName(),"Q0")==0){
			// 	Double_t pedestal = hist->GetBinCenter(hist->GetMaximumBin());
			// 	realFunc->FixParameter(i, pedestal);
			// }

			// Fix w = 0
			// if (strcmp(parameter->GetName(),"w")==0){
			// realFunc->FixParameter(i, 0);
			// }

			i++;
		}
	}


	// Set the number of points used to draw the fit function
	realFunc->SetNpx(10000);

	return realFunc;
}
