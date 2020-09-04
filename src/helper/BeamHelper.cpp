/*
 * BeamHelper.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include <iostream>
#include <TFile.h>
#include <TH2F.h>
#include <TTreeReader.h>
#include <TCanvas.h>
#include <TString.h>
#include <TObjString.h>

#include "BeamHelper.h"
#include "../model/Constants.h"
#include "../utils/HistUtils.h"
#include "../utils/GraphicsUtils.h"

BeamHelper::BeamHelper() {
	fileName = new TString();
	myFile = new TFile();
	histogramsPositive = new TList();
	histogramsNegative = new TList();
}

BeamHelper::~BeamHelper(){}

BeamHelper* BeamHelper::instance = NULL;

BeamHelper* BeamHelper::getInstance(){
    if (!instance){
        instance = new BeamHelper;
    }
    return instance;
}

int BeamHelper::init(const char* fileName){
	// Open ROOT file
	// When you create a TFile object, it becomes the current directory
	// https://root.cern.ch/root/htmldoc/guides/users-guide/InputOutput.html#the-current-directory
	this->fileName = new TString(fileName);
	myFile->Close();
	myFile = new TFile(fileName);
	if (myFile->IsZombie()) {
		std::cout << "Error opening file \"" << fileName << "\""<< std::endl;
		return -1;
	}

	// Print list of keys in ROOT file
	TList *keys = myFile->GetListOfKeys();
	keys->Print();

	for (UInt_t i = 0; i <= keys->LastIndex(); i++){
		TH1D *hist;
		TString key = ((TObjString*)keys->At(i))->GetString();
		myFile->GetObject(key.Data(), hist);
		if (hist){
			if (key.Contains("Positive")){
				histogramsPositive->Add(hist);
			}
			else {
				histogramsNegative->Add(hist);
			}
		}
	}

	// test print histograms
	// histogramsPositive->Print();
	// histogramsNegative->Print();

	return 0;
}

TList* BeamHelper::getHistogramsPositive(){
	return histogramsPositive;
}

TList* BeamHelper::getHistogramsNegative(){
	return histogramsNegative;
}
