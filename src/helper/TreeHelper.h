/*
 * TreeHelper.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_TREEHELPER_H_
#define SRC_HELPER_TREEHELPER_H_

#include <TString.h>
#include <TTree.h>
#include <TFile.h>

class TreeHelper {
public:
	static TreeHelper* getInstance();
	virtual ~TreeHelper();

	int init(const char*);
	void plotTreeProfiles();
	void plotTree(const char*);
	void fillPmtHists(TH1*, TH1*);

private:
	TreeHelper();
	static TreeHelper* instance;

	TString* fileName;
	TFile* myFile;
	TTree* myTree;
};

#endif /* SRC_HELPER_TREEHELPER_H_ */
