/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Constants.cpp
 * Author: petrstepanov
 *
 * Created on October 29, 2017, 7:34 PM
 */

// Disable warnings for -Wwrite-strings
// https://stackoverflow.com/questions/925179/selectively-remove-warning-message-gcc

#include <iostream>
#include <cstdlib>
#include <utility>
#include "Constants.h"
#include <TObjString.h>
#include "../util/StringUtils.h"

Constants::Constants(){};

Constants* Constants::instance = NULL;

Constants* Constants::getInstance(){
    if (!instance){
        instance = new Constants;
    }
    return instance;
}
const char* Constants::APPLICATION_NAME = "KaonLT Fit";

void Constants::parseParameters(int argc, char* argv[]){
	// Print command line argumants
	// Parameter with zero index [0] is the application name. So we start with [1]
	std::cout << "Command line arguments:" << std::endl;
	for (Int_t i = 1; i < argc; i++){
		std::cout << "\t" << argv[i] << std::endl;
	}

	// Parse arguments into program parameters struct
	std::cout << "\nParsing command line arguments:" << std::endl;
	for (Int_t i = 1; i < argc; i++){
		std::pair<TString,TString> pair = StringUtils::parseParameter(argv[i]);
		if (pair.first == "tree-name"){
			// Name of the TTree in the ROOT file
			parameters.treeName = pair.second;
		}
		else if (pair.first == "plot-tree"){
			// Whether to draw the TTree plots or not
			if (pair.second == "kFALSE" || pair.second == "0"){
				parameters.plotTree = kFALSE;
			}
		}
		else if (pair.first ==  "tile-profile"){
			// Tile value for the histogram projection
			parameters.tileProfile = atoi(pair.second);
		}
		else if (pair.first ==  "file-name"){
			// Add filename to the list of files
			TObjString* fileName = new TObjString(pair.second);
			parameters.inputFiles->Add(fileName);
		}
		std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
	}
}
// const std::string Constants::drawOptions[] = { "SURF2", "LEGO2" };
