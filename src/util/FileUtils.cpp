/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileUtils.cpp
 * Author: petrstepanov
 * 
 * Created on November 9, 2016, 11:41 PM
 */

#include "FileUtils.h"
#include <TUnixSystem.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <RooPlot.h>
#include <RooHist.h>
#include <RooCurve.h>
#include <TH1.h>
#include <RooAbsBinning.h>
#include "TMath.h"
#include "TMatrixD.h"
#include "../model/Constants.h"
//#include "StringUtils.h"
//#include "RootHelper.h"
//#include "Debug.h"

TH1F* FileUtils::importTH1F(std::string filename, int i) {

	int bins = 10;
	TH1F* histogram = new TH1F(TString::Format("histogram_%d", i+1), TString::Format("ROOT histogram %d", i+1), bins, 0, bins);

	return histogram;
}
