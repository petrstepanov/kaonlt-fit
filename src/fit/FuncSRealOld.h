/*
 * FuncSRealOld.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_FIT_FuncSRealOld_H_
#define SRC_FIT_FuncSRealOld_H_

#include <Rtypes.h>
#include <TH1.h>
#include <TF1.h>
#include <RooRealVar.h>
#include <iostream>
#include <vector>
#include "FuncTerm0.h"

class FuncSRealOld {
public:
	FuncSRealOld(TH1* hist, Int_t nMaxVal=100);
	virtual ~FuncSRealOld();

	Double_t func(Double_t*, Double_t*);
	TF1* getFitFunction();

private:
	TH1* hist;
	Int_t nMax;

	std::vector<TF1*> terms;    // Terms of the Ideal FuncSRealOld function (n=1..nMax)

	TF1* fitFunction;
	RooArgList* parameters;
};

#endif /* SRC_FIT_FuncSRealOld_H_ */
