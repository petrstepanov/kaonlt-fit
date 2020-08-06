/*
 * FuncSReal.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FUNCSREAL_H_
#define SRC_FIT_FUNCSREAL_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>

class FuncSReal {
public:
	FuncSReal(TH1* hist, Int_t nMaxVal=100);
	virtual ~FuncSReal();

	Double_t func(Double_t*, Double_t*);
	TF1* getFitFunction();

private:
	TH1* hist;
	Int_t nMax;
	std::vector<TF1*> functionTerms;    // Terms of the Ideal FuncSReal function (n=1..nMax)

	RooArgList* parameters;
	TF1* fitFunction;
};

#endif /* SRC_FIT_FUNCSREAL_H_ */
