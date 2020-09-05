/*
 * StringUtils.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTILS_STRINGUTILS_H_
#define SRC_UTILS_STRINGUTILS_H_

#include <iostream>
#include <utility>
#include <TString.h>
#include "../model/Constants.h"

class StringUtils {
public:
	StringUtils();
	virtual ~StringUtils();

	static std::pair<TString, TString> parseParameter(const char*);
	static TString* extractFilenameNoExtension(const char* fileNamePath);
	static TString* extractFilenameWithExtension(const char* fileNamePath);
	static const char* toString(FitType fitType);
};

#endif /* SRC_UTILS_STRINGUTILS_H_ */
