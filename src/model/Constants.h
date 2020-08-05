/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Constants.h
 * Author: petrstepanov
 *
 * Created on October 29, 2017, 7:34 PM
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <TROOT.h>
#include <TColor.h>
#include <TString.h>
#include <TList.h>

// Command-line parameters
struct Parameters {
	TString treeName = "tree1;3";
	Float_t plotTree = kTRUE;
	Int_t tileProfile = 55;
//	Int_t termsNumber = 100;
	TList* inputFiles = new TList();
};

class Constants {
  public:
	static Constants* getInstance();

	static const char* APPLICATION_NAME;

	static const Int_t TILE_BINS;
	static const Int_t TILE_MIN;
	static const Int_t TILE_MAX;

	static const Int_t CH_BINS;
	static const Int_t CH_MIN;
	static const Int_t CH_MAX;

	static const Int_t AMP_BINS;
	static const Int_t AMP_MIN;
	static const Int_t AMP_MAX;

//	static const Double_t e;

    void parseParameters(int argc, char* argv[]);

	Parameters parameters;

	private:
		Constants();
		static Constants* instance;

    // static const std::string drawOptions[2];
};

#endif /* CONSTANTS_H */
