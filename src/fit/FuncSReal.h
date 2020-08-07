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
#include "FuncTerm0.h"

class FuncSReal {
public:
	FuncSReal(TH1* hist, Int_t nMaxVal=10);
	virtual ~FuncSReal();

	Double_t func(Double_t*, Double_t*);

private:
	TH1* hist;
	Int_t nMax;

	std::vector<TF1*> terms;    // Terms of the Ideal FuncSReal function (n=1..nMax)
};

#endif /* SRC_FIT_FUNCSREAL_H_ */
