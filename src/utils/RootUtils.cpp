/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RootUtils.cpp
 * Author: petrstepanov
 *
 * Created on August 24, 2017, 8:16 PM
 */

#include "RootUtils.h"
#include "StringUtils.h"
#include "../model/Constants.h"

#include <TUnixSystem.h>
#include <TGFrame.h>
#include <TObject.h>
#include <TMatrixD.h>
#include <TMatrixDUtils.h>
#include <TString.h>
#include <TObjString.h>
#include <TList.h>
#include <TFile.h>
#include <TChain.h>
#include <TSystem.h>

#include <RooHist.h>
#include <RooPlot.h>

#include <iostream>
#include <utility>

void RootUtils::deleteObject(const char* name){
    TObject* obj = gROOT->FindObject(name);
    deleteObject(obj);
}

void RootUtils::deleteObject(TObject* obj){
    if (obj){
        obj->Delete();
    }
}

Int_t RootUtils::getNumCpu(){
    SysInfo_t sysInfo;
    gSystem->GetSysInfo(&sysInfo);
    std::cout << "RootUtils::getNumCpu: sysInfo.fCpus = " << sysInfo.fCpus << std::endl;
    return (sysInfo.fCpus >= 0) ? sysInfo.fCpus : 1;
}

TStopwatch* RootUtils::watch = new TStopwatch();

void RootUtils::startTimer(){
	watch->Reset();
    watch->Start();
}

void RootUtils::stopAndPrintTimer(){
    watch->Stop();
    watch->Print();
	printf("Real time = %7.3f s, Cpu Time = %7.3f s\n", watch->RealTime(), watch->CpuTime());
}

InputFileType RootUtils::getInputFileType(const char* fileName){
	// Open ROOT file
	TFile *myFile = new TFile(fileName);
	if (myFile->IsZombie()) {
		std::cout << "Error opening file \"" << fileName << "\""<< std::endl;
		return InputFileType::Unknown;
	}

	// Get list of keys in ROOT file
	TList *keysList = myFile->GetListOfKeys();

	// Prototype spectra contain "tree1"
	if (keysList->FindObject("tree1")){
		return InputFileType::Prototype;
	}

	// Prototype spectra contain "tree1"
	if (keysList->FindObject("Positive_PMT_0")){
		return InputFileType::Beam;
	}

	return InputFileType::Unknown;
}

TFile* RootUtils::mergeFiles(TList* fileNamesList){
	// If no files provides
	if (fileNamesList->LastIndex() < 0) return NULL;

	// If one filename provided
	const char* firstFileName = (((TObjString*)fileNamesList->At(0))->GetString()).Data();
	if (fileNamesList->LastIndex() == 0){
		TFile* file = new TFile(firstFileName);
		if (file->IsZombie()) {
			std::cout << "Error opening file \"" << firstFileName << "\""<< std::endl;
			return NULL;
		}
		return file;
	}

	// If multiple filenames provided - import file names into the chain
	TString* firstFileNameNoExt = StringUtils::extractFilenameNoExtension(firstFileName);
	TString chainName = TString::Format("chain-%s", firstFileNameNoExt->Data());
	TChain* chain = new TChain(chainName.Data());
	for (TObject* object : *fileNamesList) {
		TObjString* objString = (TObjString*)object;
		if (objString){
			Int_t result = chain->Add(objString->GetString().Data());
			if (result == 0) return NULL;
		}
	}

	// Construct new TFile name and merge TChain into it
	TString* firstFileNameWithExt = StringUtils::extractFilenameNoExtension(firstFileName);
	TString newFileName = firstFileNameWithExt->ReplaceAll(".root", "-all.root");
	const char* absFilePath = gSystem->PrependPathName(gSystem->WorkingDirectory(), newFileName);
	Int_t result = chain->Merge(absFilePath);
	if (result == 0){
		std::cout << "Error merging to file \"" << absFilePath << "\""<< std::endl;
		return NULL;
	}

	// Open merged file and return it
	TFile* file = new TFile(absFilePath);
	if (file->IsZombie()) {
		std::cout << "Error opening file \"" << absFilePath << "\""<< std::endl;
		return NULL;
	}
	return file;
}
