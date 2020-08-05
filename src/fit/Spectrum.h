/*
 * Spectrum.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_SPECTRUM_H_
#define SRC_FIT_SPECTRUM_H_

#include <Rtypes.h>
#include <RooRealVar.h>

class Spectrum {
public:
	Spectrum(Double_t histIntegralVal, Int_t xMin, Int_t xMax, Int_t nMaxVal=100);
	virtual ~Spectrum();

//	Double_t ideal(Double_t*, Double_t*);
//	Double_t background(Double_t*, Double_t*);

	Double_t realIndefInt(Double_t , Double_t*);
	Double_t realDefInt(Double_t*);
	Double_t realDefIntSimple(Double_t*);
	Double_t real(Double_t*, Double_t*);
	Double_t exponent(Double_t* _x, Double_t* par);
	Double_t gauss(Double_t* _x, Double_t* par, Double_t n);
	static RooArgList* parameters;

private:
	Int_t nMax;
	Int_t xMax;
	Int_t xMin;
	Double_t histIntegral;
	Double_t pi;
	Double_t e;
};

#endif /* SRC_FIT_SPECTRUM_H_ */
