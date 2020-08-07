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

#include "../utils/StringUtils.h"

Constants::Constants(){};

Constants* Constants::instance = NULL;

Constants* Constants::getInstance(){
    if (!instance){
        instance = new Constants;
    }
    return instance;
}
const char* Constants::APPLICATION_NAME = "KaonLT Fit";

// Variable limits set experimentally by zooming into axis
// ----------+-------+------------------+----------------+
// Variable  | bins  | lo_bin_left_edge | hi_bin_up_edge |
// ----------+-------+------------------+----------------+
// Channels  | 21000 |            -1000 |          20000 |
// Tile      |   145 |                1 |            146 |
// Amplitude |  4096 |                0 |           4096 |
// ----------+-------+------------------+----------------+

const Int_t Constants::TILE_BINS = 145;
const Int_t Constants::TILE_MIN = 1;
const Int_t Constants::TILE_MAX = 146;

const Int_t Constants::CH_BINS = 21000;
const Int_t Constants::CH_MIN = -1000;
const Int_t Constants::CH_MAX = 5000;

const Int_t Constants::AMP_BINS = 4096;
const Int_t Constants::AMP_MIN = 0;
const Int_t Constants::AMP_MAX = 4096;

// const Double_t Constants::e = 1.6e−19;


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
		else if (pair.first ==  "terms-number"){
			// Number of terms in the fitting function
			parameters.termsNumber = atoi(pair.second);
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
