/*
 * StringUtils.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include "../utils/StringUtils.h"

#include "TPRegexp.h"
#include "TObjString.h"
#include "TObjArray.h"

StringUtils::StringUtils() {
	// TODO Auto-generated constructor stub

}

StringUtils::~StringUtils() {
	// TODO Auto-generated destructor stub
}

std::pair<TString, TString> StringUtils::parseParameter(const char* parameter){
	TString s4(parameter);
	// Test regex here: https://regex101.com/r/7H6We8/1 and remember c++ double escapes!
	// Check if parameter is a variable
	TObjArray *subStr1 = TPRegexp("^--(.+)=(.+)$").MatchS(s4);
	const Int_t nrSubStr1 = subStr1->GetLast()+1;
	if (nrSubStr1 == 3) {
		const TString name = ((TObjString *)subStr1->At(1))->GetString();
		const TString value  = ((TObjString *)subStr1->At(2))->GetString();
		return std::make_pair(name, value);
	}

	// Check if parameter is a ROOT file
	TObjArray *subStr2 = TPRegexp("^(.+)\\.root$").MatchS(s4);
	const Int_t nrSubStr2 = subStr2->GetLast()+1;
	if (nrSubStr2 == 2) {
		return std::make_pair(TString("file-name"), TString(parameter));
	}

	// Otherwise return "unknown" in pair
	return std::make_pair(TString("unknown-argument"), TString(parameter));
}
