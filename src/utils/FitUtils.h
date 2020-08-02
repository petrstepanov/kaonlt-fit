/*
 * FitUtils.h
 *
 *  Created on: Aug 2, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_FITUTILS_H_
#define SRC_UTILS_FITUTILS_H_

#include <RtypesCore.h>
#include <TF1.h>
#include <TH1.h>

class FitUtils {
public:
	FitUtils();
	virtual ~FitUtils();

	static TF1* getConvFitFunction(Double_t xMin, Double_t xMax);
	static TF1* getRealFitFunction(TH1* hist);
};

#endif /* SRC_UTILS_FITUTILS_H_ */
