/*
 * BeamHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_BeamHelper_H_
#define SRC_HELPER_BeamHelper_H_

#include <TList.h>
#include <TString.h>
#include <TTree.h>

class BeamHelper {
public:
	static BeamHelper* getInstance();
	virtual ~BeamHelper();

	int init(TList*);
	TList* getHistogramsPositive();
	TList* getHistogramsNegative();
	const char* getFileName();

private:
	BeamHelper();
	static BeamHelper* instance;

	TFile* myFile;

	TList* histogramsPositive;
	TList* histogramsNegative;
};

#endif /* SRC_HELPER_BeamHelper_H_ */
