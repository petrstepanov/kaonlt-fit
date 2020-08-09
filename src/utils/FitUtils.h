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

class FitUtils {
public:
	FitUtils();
	virtual ~FitUtils();

	static TF1* getFuncSReal(TH1*, Int_t, Bool_t isFFT = kFALSE);
	static void doFit(TH1* hist);
	static void doRooFit(TH1* hist);
	static void doRooFit2(TH1* hist);

private:
	static RooRealVar* Q0;
	static RooRealVar* s0;
	static RooRealVar* Q1;
	static RooRealVar* s1;
	static RooRealVar* w;
	static RooRealVar* a;
	static RooRealVar* mu;
};

#endif /* SRC_UTILS_FITUTILS_H_ */
