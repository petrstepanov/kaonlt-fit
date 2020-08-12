/*
 * HistUtils.h
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_HISTUTILS_H_
#define SRC_UTILS_HISTUTILS_H_

#include <iostream>
#include <TH1F.h>

class HistUtils {
public:
	HistUtils();
	virtual ~HistUtils();

	static TH1* trimHistogram(TH1*);
	static TH1* trimHistogram(TH1*, Int_t, Int_t);
	static TH1* cloneHistogram(TH1*, const char*, const char* = 0);
	static void resetHistogram(TH1*);
	static void increaseBinContent(TH1*, Float_t);
};

#endif /* SRC_UTILS_HISTUTILS_H_ */
