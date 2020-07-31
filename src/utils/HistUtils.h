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
	static void resetHistogram(TH1*);
	static void increaseBinContent(TH1*, Float_t);
};

#endif /* SRC_UTILS_HISTUTILS_H_ */
