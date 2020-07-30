/*
 * StringUtils.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_UTIL_STRINGUTILS_H_
#define SRC_UTIL_STRINGUTILS_H_

#include <iostream>
#include <utility>
#include <TString.h>

class StringUtils {
public:
	StringUtils();
	virtual ~StringUtils();

	static std::pair<TString, TString> parseParameter(const char*);
};

#endif /* SRC_UTIL_STRINGUTILS_H_ */
