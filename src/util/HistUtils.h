/*
 * HistUtils.h
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTIL_HISTUTILS_H_
#define SRC_UTIL_HISTUTILS_H_

#include <iostream>
#include <TH1F.h>

class HistUtils {
public:
	HistUtils();
	virtual ~HistUtils();

	static TH1* trimHistogram(TH1*);
	static void resetHistogram(TH1*);
};

#endif /* SRC_UTIL_HISTUTILS_H_ */
