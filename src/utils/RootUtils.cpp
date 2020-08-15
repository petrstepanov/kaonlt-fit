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
#include <TList.h>

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
