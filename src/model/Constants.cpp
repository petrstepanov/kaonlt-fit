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
#include <RooRealVar.h>
#include "../utils/StringUtils.h"


Constants::Constants(){
};

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

const Int_t Constants::CH_BINS = 2100;
const Int_t Constants::CH_MIN_VAL = -1000;
const Int_t Constants::CH_MAX_VAL = 20000;

const Int_t Constants::CH_FIT_MIN_VAL = 1;
const Int_t Constants::CH_FIT_MAX_VAL = 2000;


const Int_t Constants::AMP_MIN = 0;
const Int_t Constants::AMP_MAX = 4096;

const Int_t Constants::N_PX = 2048;

// Parse command line parameters
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
		else if (pair.first == "plot-profiles"){
			// Whether to draw the TTree plots or not
			if (pair.second == "kFALSE" || pair.second == "0"){
				parameters.plotProfiles = kFALSE;
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
		else if (pair.first ==  "convolution-bins"){
			// Number of terms in the fitting function
			parameters.convolutionBins = atoi(pair.second);
		}
		else if (pair.first ==  "file-name"){
			// Add filename to the list of files
			TObjString* fileName = new TObjString(pair.second);
			parameters.inputFiles->Add(fileName);
		}
		else if (pair.first == "fit"){
			if (pair.second == "root"){
				parameters.fitType = FitType::root;
			} else if (pair.second == "rootconv" || pair.second == "rootConv"){
				parameters.fitType = FitType::rootConv;
			} else {
				parameters.fitType = FitType::rooFit;
			}
		}
		else if (pair.first == "params-filename"){
			// Name of the file with parameters
			parameters.fitParamsFileName = pair.second;
		}
		std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
	}
}
