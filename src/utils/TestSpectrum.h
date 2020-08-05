/*
 * TestSpectrum.h
 *
 *  Created on: Aug 4, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_TESTSPECTRUM_H_
#define SRC_UTILS_TESTSPECTRUM_H_

#include <TH1.h>

class TestSpectrum {
public:
//	static TestSpectrum* getInstance();
	TestSpectrum();
	virtual ~TestSpectrum();

	static TH1* getHistogram();

private:
//	static TestSpectrum* instance;
	static Int_t array[];
};

#endif /* SRC_UTILS_TESTSPECTRUM_H_ */
