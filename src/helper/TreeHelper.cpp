/*
 * TreeHelper.cpp
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

#include "TreeHelper.h"
#include "../model/Constants.h"
#include "../utils/HistUtils.h"
#include "../utils/GraphicsUtils.h"

TreeHelper::TreeHelper() {
	fileName = new TString();
	myFile = new TFile();
	myTree = new TTree();
}

TreeHelper::~TreeHelper(){}

TreeHelper* TreeHelper::instance = NULL;

TreeHelper* TreeHelper::getInstance(){
    if (!instance){
        instance = new TreeHelper;
    }
    return instance;
}

int TreeHelper::init(const char* fileName){
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
	myFile->GetListOfKeys()->Print(); // or file->ls()

	// Read Tree from ROOT file
	myFile->GetObject(Constants::getInstance()->parameters.treeName, myTree); // or gDirectory->GetObject("T",MyTree);
	myTree->Print();     // Print tree branches
	// myTree->Scan("");    // Print tree columns

	return 0;
}

void TreeHelper::plotTreeProfiles(){
	// Construct histograms for the TTree profiles (ch_1 and ch_2)
	TH1F* ch1Hist = new TH1F("ch1Hist", "Channel profile for PMT1", Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	ch1Hist->GetXaxis()->SetTitle("Events");
	ch1Hist->SetStats(0);
	ch1Hist->GetYaxis()->SetTitle("Channel (ch_1)");
	TH1F* ch2Hist = new TH1F("ch2Hist", "Channel profile for PMT2", Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	ch2Hist->GetXaxis()->SetTitle("Events");
	ch2Hist->SetStats(0);
	ch2Hist->GetYaxis()->SetTitle("Channel (ch_2)");

	const char* treeName = myTree->GetName(); //Constants::getInstance()->parameters.treeName.Data();
	TString myCanvasName = TString::Format("%s-ch_1-ch_2", treeName);
	TString myCanvasTitle = TString::Format("TTree \"%s\" channel profiles. File \"%s\"", treeName, fileName);
	TCanvas* myCanvas = new TCanvas(myCanvasName, myCanvasTitle, 1024, 512);
	myCanvas->Divide(2,1);

	TVirtualPad* pad1 = myCanvas->cd(1);
	pad1->SetLogz();
	pad1->SetLeftMargin(0.15);
	pad1->SetRightMargin(0.15);
	myTree->Draw("ch_1>>ch1Hist","",""); // no canvas, draw directly to histogram
	pad1->SetLogy();
	ch1Hist->Draw();
	// GraphicsUtils::alignStats(ch1Hist, pad1);

	TVirtualPad* pad2 = myCanvas->cd(2);
	pad2->SetLogz();
	pad2->SetLeftMargin(0.15);
	pad2->SetRightMargin(0.15);
	myTree->Draw("ch_2>>ch2Hist","",""); // no canvas, draw directly to histogram
	pad2->SetLogy();
	ch2Hist->Draw();
	// GraphicsUtils::alignStats(ch2Hist, pad2);

	// Save canvas to file
	// TString pngFilePath = TString(myCanvas->GetName()) + ".png";
	// myCanvas->SaveAs(pngFilePath);
}

void TreeHelper::plotTree(const char* fileName){
	// Construct histograms (ch_1:tilel) and (ch_2:tiler) from the TTree
	TH2F* ch1TilelHist = new TH2F("ch1TilelHist", "Channel vs Tile for PMT1",
								  Constants::TILE_BINS, Constants::TILE_MIN, Constants::TILE_MAX,
								  Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	ch1TilelHist->GetXaxis()->SetTitle("Tile (tilel)");
	ch1TilelHist->GetYaxis()->SetTitle("Channel (ch_1)");
	ch1TilelHist->SetStats(0);
	TH2F* ch2TilerHist = new TH2F("ch2TilerHist", "Channel vs Tile for PMT2",
			   	   	   	   	   	  Constants::TILE_BINS, Constants::TILE_MIN, Constants::TILE_MAX,
								  Constants::CH_BINS, Constants::CH_MIN_VAL, Constants::CH_MAX_VAL);
	ch2TilerHist->GetXaxis()->SetTitle("Tile (tiler)");
	ch2TilerHist->GetYaxis()->SetTitle("Channel (ch_2)");
	ch2TilerHist->SetStats(0);
	// Construct histograms (amp_1:tilel) and (amp_2:tiler) from the TTree
	TH2F* amp1TilelHist = new TH2F("amp1TilelHist", "Amplitude vs Tile for PMT1",
			  	  	  	  	  	   Constants::TILE_BINS, Constants::TILE_MIN, Constants::TILE_MAX,
								   Constants::AMP_MAX-Constants::AMP_MIN, Constants::AMP_MIN, Constants::AMP_MAX);
	amp1TilelHist->GetXaxis()->SetTitle("Tile (tilel)");
	amp1TilelHist->GetYaxis()->SetTitle("Amplitude (amp_1)");
	amp1TilelHist->SetStats(0);
	TH2F* amp2TilerHist = new TH2F("amp2TilerHist", "Amplitude vs Tile for PMT2",
								   Constants::TILE_BINS, Constants::TILE_MIN, Constants::TILE_MAX,
								   Constants::AMP_MAX-Constants::AMP_MIN, Constants::AMP_MIN, Constants::AMP_MAX);
	amp2TilerHist->GetXaxis()->SetTitle("Tile (tiler)");
	amp2TilerHist->GetYaxis()->SetTitle("Amplitude (amp_2)");
	amp2TilerHist->SetStats(0);

	const char* treeName = myTree->GetName();
	TString myCanvasName = TString::Format("%s-ch:tile-amp:tile", treeName);
	TString myCanvasTitle = TString::Format("TTree \"%s\". File \"%s\"", treeName, fileName);
	TCanvas* myCanvas = new TCanvas(myCanvasName, myCanvasTitle, 1024, 1024);
	myCanvas->Divide(2,2);

	TVirtualPad* pad1 = myCanvas->cd(1);
	pad1->SetLogz();
	pad1->SetLeftMargin(0.15);
	pad1->SetRightMargin(0.15);
	myTree->Draw("ch_1:tilel>>ch1TilelHist","","COLZ0"); // no canvas, draw directly to histogram
	ch1TilelHist->Draw("COLZ0");

	TVirtualPad* pad2 = myCanvas->cd(2);
	pad2->SetLogz();
	pad2->SetLeftMargin(0.15);
	pad2->SetRightMargin(0.15);
	myTree->Draw("ch_2:tiler>>ch2TilerHist","","COLZ0"); // no canvas, draw directly to histogram
	// myTree->Draw("ch_2:tiler>>htemp(100,10,,50,.1,.5)","","COLZ0");
	// ch2TilerHist = (TH2F*)gPad->GetPrimitive("htemp")->Clone("ch2TilerHist");
	ch2TilerHist->Draw("COLZ0");

	TVirtualPad* pad3 = myCanvas->cd(3);
	pad3->SetLogz();
	pad3->SetRightMargin(0.15);
	pad3->SetLeftMargin(0.15);
	// myTree->Draw("amp_1:tilel", "", "COLZ0");
	myTree->Draw("amp_1:tilel>>amp1TilelHist","","COLZ0"); // no canvas, draw directly to histogram
	amp1TilelHist->Draw("COLZ0");

	TVirtualPad* pad4 = myCanvas->cd(4);
	pad4->SetLogz();
	pad4->SetLeftMargin(0.15);
	pad4->SetRightMargin(0.15);
	// myTree->Draw("amp_2:tiler", "", "COLZ0");
	myTree->Draw("amp_2:tiler>>amp2TilerHist","","COLZ0");
	amp2TilerHist->Draw("COLZ0");

	// Save canvas to file
	TString pngFilePath = TString::Format("%s-%s.png",fileName, treeName);
	myCanvas->SaveAs(pngFilePath.Data());
}

void TreeHelper::fillPmtHists(TH1* pmt1Hist, TH1* pmt2Hist){
	// Iterate through the events via TTreeReader class
	// https://stackoverflow.com/questions/28329457/cern-root-how-to-read-contents-from-a-ttree-root-file-into-array
	TTreeReader myReader(myTree);
	// TTreeReader myReader(Constants::TREE_NAME, myFile);
	TTreeReaderValue<Int_t> tilel(myReader, "tilel");
	TTreeReaderValue<Int_t> tiler(myReader, "tiler");
	TTreeReaderValue<Float_t> amp_1(myReader, "amp_1");
	TTreeReaderValue<Float_t> amp_2(myReader, "amp_2");
	TTreeReaderValue<Float_t> ch_1(myReader, "ch_1");
	TTreeReaderValue<Float_t> ch_2(myReader, "ch_2");
	while (myReader.Next()) {
		// std::cout << *tilel << " " << *tiler << " " << *amp_1 << " " << *amp_2  << " " << *ch_1 << " " << *ch_2 << std::endl;
		Int_t tileProfile = Constants::getInstance()->parameters.tileProfile;
		if (*tilel == tileProfile && *tiler > 0){ // tilel, ch_1 && tiler !=0
			HistUtils::increaseCorrespondingBinContent(pmt1Hist, *ch_1);
		}
		if (*tiler == tileProfile && *tilel > 0){
			HistUtils::increaseCorrespondingBinContent(pmt2Hist, *ch_2);
		}
	}
}
