#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include <iostream>
#include <TApplication.h>
#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TStyle.h>

#include "model/Constants.h"
#include "util/HistUtils.h"
#include "util/TreeUtils.h"


int run() {

	int argc = gApplication->Argc();
	char** argv = gApplication->Argv();

	// Check if spectra filenames are passed as parameters
	if(argc == 1){
		std::cout << "No spectra files specified." << std::endl;
		return 1;
	}

	// Iterate through parameters and fit every spectrum
	for (int i = 1; i < gApplication->Argc(); i++){
		TFile* myFile = new TFile(argv[i]);
		// When you create a TFile object, it becomes the current directory
		// https://root.cern.ch/root/htmldoc/guides/users-guide/InputOutput.html#the-current-directory

		if (myFile->IsZombie()) {
			std::cout << "Error opening file \"" << argv[i] << "\""<< std::endl;
			exit(-1);
		} else {
			// Print list of keys in tfile
			myFile->GetListOfKeys()->Print(); // or file->ls()

			// Get tree with name 'tree1' and cycle number 3 from the TFile
			TTree *myTree;
			gDirectory->GetObject(Constants::TREE_NAME, myTree);
			myTree->Print(); // Print tree branches
			// myTree->Scan("");

			// TH1* ch1Hist = TreeUtils::GetBranchHistogram(myTree, "ch_1");
			// TCanvas* ch1Canvas = new TCanvas("ch1Canvas", "ch_1 Canvas");
			// ch1Canvas->SetLogy();
			// ch1Hist->Draw();

			// TCanvas* ch1TrimmedCanvas = new TCanvas("ch1TrimmedCanvas", "ch1TrimmedCanvas");
			// ch1TrimmedCanvas->SetLogy();
			// TH1* ch1HistTrimmed = HistUtils::trimHistogram(ch1Hist);
			// ch1HistTrimmed->Draw();

			// Plot histograms with PMT data
			if (Constants::DO_PLOT_TREE){
				TString myCanvasName = TString::Format("TTree \"%s\" from \"%s\" file", Constants::TREE_NAME, argv[i]);
				TCanvas* myCanvas = new TCanvas(myCanvasName, myCanvasName, 1000, 400);
				myCanvas->Divide(2,1);
				TVirtualPad* pad1 = myCanvas->cd(1);
				pad1->SetTitle("PMT1 tilel:ch_1:amp_1");
				pad1->SetLogz();
				pad1->SetRightMargin(0.16);
				myTree->Draw("tilel:ch_1:amp_1","","COLZ");

				TVirtualPad* pad2 = myCanvas->cd(2);
				pad2->SetTitle("PMT2 tiler:ch_2:amp_2");
				pad2->SetLogz();
				pad2->SetRightMargin(0.16);
				myTree->Draw("tiler:ch_2:amp_2","","COLZ");
			}

			if (Constants::DO_PLOT_PROFILES){
				// Prepare histograms for the sliced spectra
				TH1* pmt1Hist = TreeUtils::GetBranchHistogram(myTree, "ch_1", "pmt1Hist");
				TCanvas* pmt1Canvas = new TCanvas("pmt1Canvas", "pmt_1 Canvas");
				pmt1Canvas->SetLogy();
				pmt1Hist->DrawClone();
				HistUtils::resetHistogram(pmt1Hist);

				TH1* pmt2Hist = TreeUtils::GetBranchHistogram(myTree, "ch_2", "pmt2Hist");
				TCanvas* pmt2Canvas = new TCanvas("pmt2Canvas", "pmt_2 Canvas");
				pmt2Canvas->SetLogy();
				pmt2Hist->DrawClone();
				HistUtils::resetHistogram(pmt2Hist);

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
					if (*tilel == Constants::TILE_PROFILE && *amp_1 != 0){
						// std::cout << *tilel << " " << *tiler << " " << *amp_1 << " " << *amp_2  << " " << *ch_1 << " " << *ch_2 << std::endl;
						Int_t bin = pmt1Hist->GetXaxis()->FindBin(*ch_1);
						if (bin >= 1 && bin <= pmt1Hist->GetNbinsX()){
							pmt1Hist->SetBinContent(bin, *amp_1);
						}
					}
					if (*tiler == Constants::TILE_PROFILE && *amp_2 != 0){
						// std::cout << *tilel << " " << *tiler << " " << *amp_1 << " " << *amp_2  << " " << *ch_1 << " " << *ch_2 << std::endl;
						Int_t bin = pmt2Hist->GetXaxis()->FindBin(*ch_2);
						if (bin >= 1 && bin <= pmt2Hist->GetNbinsX()){
							pmt2Hist->SetBinContent(bin, *amp_2);
						}
					}
				}

				// Plot PMT profile spectra
				TString pmtsCanvasTitle = TString::Format("Profile of the PMT spectra (tile = %d)", Constants::TILE_PROFILE);
				TCanvas* pmtsCanvas = new TCanvas("pmtsCanvas", pmtsCanvasTitle, 1000, 400);
				pmtsCanvas->Divide(2,1);
				// pmtsCanvas->cd(1);
				TVirtualPad* pmtsCanvasPad1 = pmtsCanvas->cd(1);
				pmtsCanvasPad1->SetLogy();
				pmt1Hist->Draw();
				// pmtsCanvas->cd(2);
				TVirtualPad* pmtsCanvasPad2 = pmtsCanvas->cd(2);
				pmtsCanvasPad2->SetLogy();
				pmt2Hist->Draw();
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {
	// Create ROOT application
	// https://github.com/root-project/root/blob/master/tutorials/gui/mditest.C#L409
	TApplication* app = new TApplication(Constants::APPLICATION_NAME, &argc, argv);
	run();
	app->Run();
	return 0;
}
