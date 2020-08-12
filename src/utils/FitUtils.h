/*
 * FitUtils.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_FITUTILS_H_
#define SRC_UTILS_FITUTILS_H_

#include <TH1.h>
#include <RooRealVar.h>

#include "../fit/AbsComponentFunc.h"

class FitUtils {
public:
	FitUtils();
	virtual ~FitUtils();

	static void doFit(TH1* hist, AbsComponentFunc* funcObject);
	static void doFitTest(TH1* hist);
	static void doRooFit(TH1* hist, Bool_t doConvolution);
	static void fillHistogramFromFuncObject(TH1* hist, AbsComponentFunc* funcObject);
	static TH1* getfillHistogramFromFuncObject(TH1* hist, AbsComponentFunc* funcObject);
	static Double_t* getConvFitParameters(Double_t*, Int_t nPar);

private:
	static void doRooFitConvolution(TH1* hist);
	static void doRooFitNoConvolution(TH1* hist);
	static TF1* getFuncSReal(TH1*, Int_t, Bool_t isConvolution = kFALSE);

	static RooRealVar* Q0;
	static RooRealVar* s0;
	static RooRealVar* Q1;
	static RooRealVar* s1;
	static RooRealVar* w;
	static RooRealVar* a;
	static RooRealVar* mu;
};

#endif /* SRC_UTILS_FITUTILS_H_ */
