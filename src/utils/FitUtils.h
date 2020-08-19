/*
 * FitUtils.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_FITUTILS_H_
#define SRC_UTILS_FITUTILS_H_

#include <TH1.h>
#include <TVirtualPad.h>
#include <RooRealVar.h>

#include "../fit/AbsComponentFunc.h"
#include "../model/FitParameters.h"

class FitUtils {
public:
	FitUtils();
	virtual ~FitUtils();

	static void doFit(TH1* hist, FitParameters* pars, AbsComponentFunc* funcObject, Int_t fitMin = 0, TVirtualPad* pad = 0, Bool_t noTerm0 = kFALSE);
	static void doFitTest(TH1* hist, FitParameters* pars);
	static void doRooFit(TH1* hist, FitParameters* pars, Bool_t useTerm0 = kTRUE, Int_t fitMin = 0, TVirtualPad* pad = 0);
	static void fillHistogramFromFuncObject(TH1* hist, FitParameters* pars, AbsComponentFunc* funcObject);
	static TH1* getfillHistogramFromFuncObject(TH1* hist, AbsComponentFunc* funcObject);
	static Double_t* getConvFitParameters(Double_t*, Int_t nPar);

private:
	static TF1* getFuncSReal(TH1*, Int_t, Bool_t isConvolution = kFALSE);
};

#endif /* SRC_UTILS_FITUTILS_H_ */
