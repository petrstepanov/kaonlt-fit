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
	Spectrum(Int_t);
	virtual ~Spectrum();

	Double_t ideal(Double_t*, Double_t*);
	Double_t background(Double_t*, Double_t*);
	Double_t real(Double_t*, Double_t*);

	static RooArgList* parameters;

private:
	Int_t nMax;
	Double_t pi;
	Double_t e;
};

#endif /* SRC_FIT_SPECTRUM_H_ */
