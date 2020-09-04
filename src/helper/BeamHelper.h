/*
 * BeamHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_BeamHelper_H_
#define SRC_HELPER_BeamHelper_H_

#include <TString.h>
#include <TTree.h>
#include <TFile.h>

class BeamHelper {
public:
	static BeamHelper* getInstance();
	virtual ~BeamHelper();

	int init(const char*);
	TList* getHistogramsPositive();
	TList* getHistogramsNegative();

private:
	BeamHelper();
	static BeamHelper* instance;

	TString* fileName;
	TFile* myFile;

	TList* histogramsPositive;
	TList* histogramsNegative;
};

#endif /* SRC_HELPER_BeamHelper_H_ */
