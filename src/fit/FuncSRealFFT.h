/*
 * FuncSRealFFT.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncSRealFFT_H_
#define SRC_FIT_FuncSRealFFT_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>

class FuncSRealFFT {
public:
	FuncSRealFFT(TH1* hist, Int_t nMaxVal=100);
	virtual ~FuncSRealFFT();

	Double_t func(Double_t*, Double_t*);

private:
	TH1* hist;
	Int_t nMax;

	std::vector<TF1*> terms;    // Terms of the Ideal FuncSRealFFT function (n=1..nMax)
};

#endif /* SRC_FIT_FuncSRealFFT_H_ */
