/*
 * TreeUtils.h
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTIL_TREEUTILS_H_
#define SRC_UTIL_TREEUTILS_H_

#include <iostream>
#include <TH1.h>
#include <TTree.h>

class TreeUtils {
public:
	TreeUtils();
	virtual ~TreeUtils();

	static TH1* GetBranchHistogram(TTree*, const char*, const char*);
};

#endif /* SRC_UTIL_TREEUTILS_H_ */
