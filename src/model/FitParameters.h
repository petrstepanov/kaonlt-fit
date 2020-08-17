/*
 * FitParameters.h
 *
 *  Created on: Aug 16, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_MODEL_FITPARAMETERS_H_
#define SRC_MODEL_FITPARAMETERS_H_

#include <RtypesCore.h>
#include <RooArgList.h>
#include <RooRealVar.h>

enum class ParametersType {
	forBellamyHist,
	forKaonHist
};

class FitParameters {
public:
	FitParameters(ParametersType parType);
	virtual ~FitParameters();

	RooArgList* getList();
	Double_t* getArray();
	Int_t getSize();

	RooRealVar *Q0, *s0, *Q1, *s1, *w, *a, *mu;

private:
	RooArgList* parameters;
};

#endif /* SRC_MODEL_FITPARAMETERS_H_ */
