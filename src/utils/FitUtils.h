/*
 * FitUtils.h
 *
 *  Created on: Aug 6, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_FITUTILS_H_
#define SRC_UTILS_FITUTILS_H_

#include <TH1.h>

class FitUtils {
public:
	FitUtils();
	virtual ~FitUtils();

	static TF1* getFuncSReal(TH1*, Int_t);

private:

};

#endif /* SRC_UTILS_FITUTILS_H_ */
