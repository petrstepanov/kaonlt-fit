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
#include <RooArgList.h>
#include <RooRealVar.h>

// Command-line parameters

enum class FitType {
	test,
	root,
	rootConv,
	rooFit
};

enum class Minimization {
	chi2,
	likelihood
};

struct Parameters {
	TString treeName = "tree1;3";
	Float_t plotTree = kTRUE;
	Float_t plotProfiles = kTRUE;
	Int_t tileProfile = 55;
	Int_t termsNumber = 50;
	Int_t convolutionBins = 1024;
	FitType fitType = FitType::root;
	Minimization minimize = Minimization::chi2;
	TList* inputFiles = new TList();
	TString fitParamsFileName = "fit-parameters.txt";
};

class Constants {
  public:
	static Constants* getInstance();

	static const char* APPLICATION_NAME;

	static const Int_t TILE_BINS;
	static const Int_t TILE_MIN;
	static const Int_t TILE_MAX;

	static const Int_t CH_BINS;
	static const Int_t CH_MIN_VAL;
	static const Int_t CH_MAX_VAL;

	static const Int_t CH_FIT_MIN_VAL;
	static const Int_t CH_FIT_MAX_VAL;

	static const Int_t AMP_MIN;
	static const Int_t AMP_MAX;

	static const Int_t N_PX;

	static const Double_t SIGMA_TO_FWHM;

	Parameters parameters;
    void parseParameters(int argc, char* argv[]);

private:
	Constants();
	static Constants* instance;
};

#endif /* CONSTANTS_H */
