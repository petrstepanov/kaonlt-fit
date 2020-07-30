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
#include <TH2.h>
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
			myFile->GetObject(Constants::TREE_NAME, myTree); // or gDirectory->GetObject("T",MyTree);
			myTree->Print(); // Print tree branches
			// myTree->Scan(""); // Print tree columns

			// TH1* ch1Hist = TreeUtils::GetBranchHistogram(myTree, "ch_1");
			// TCanvas* ch1Canvas = new TCanvas("ch1Canvas", "ch_1 Canvas");
			// ch1Canvas->SetLogy();
			// ch1Hist->Draw();

			// TCanvas* ch1TrimmedCanvas = new TCanvas("ch1TrimmedCanvas", "ch1TrimmedCanvas");
			// ch1TrimmedCanvas->SetLogy();
			// TH1* ch1HistTrimmed = HistUtils::trimHistogram(ch1Hist);
			// ch1HistTrimmed->Draw();


			// Variable limits set experimentally by zooming into axis

			// ----------+-------+------------------+----------------+
			// Variable  | bins  | lo_bin_left_edge | hi_bin_up_edge | description
			// ----------+-------+------------------+----------------+
			// Channels  | 21000 |            -1000 |          20000 |
			// Tile      |   145 |                1 |            146 |
			// Amplitude |  4096 |                0 |           4096 | Analyzer bins
			// ----------+-------+------------------+----------------+

			// Histograms (ch_1:tilel) and (ch_2:tiler) from the TTree
			TH2F *ch1TilelHist = new TH2F("ch1TilelHist", "Channel vs Tile for PMT1", 145, 1, 146, 21000, -1000, 20000);
			ch1TilelHist->GetXaxis()->SetTitle("Tile (tilel)");
			ch1TilelHist->GetYaxis()->SetTitle("Channel (ch_1)");
			ch1TilelHist->SetStats(0);
			TH2F *ch2TilerHist = new TH2F("ch2TilerHist", "Channel vs Tile for PMT2", 145, 1, 146, 21000, -1000, 20000);
			ch2TilerHist->GetXaxis()->SetTitle("Tile (tiler)");
			ch2TilerHist->GetYaxis()->SetTitle("Channel (ch_2)");
			ch2TilerHist->SetStats(0);
			// Histograms (amp_1:tilel) and (amp_2:tiler) from the TTree
			TH2F *amp1TilelHist = new TH2F("amp1TilelHist", "Amplitude vs Tile for PMT1", 145, 1, 146, 4096, 0, 4096);
			amp1TilelHist->GetXaxis()->SetTitle("Tile (tilel)");
			amp1TilelHist->GetYaxis()->SetTitle("Amplitude (amp_1)");
			amp1TilelHist->SetStats(0);
			TH2F *amp2TilerHist = new TH2F("amp2TilerHist", "Amplitude vs Tile for PMT2", 145, 1, 146, 4096, 0, 4096);
			amp2TilerHist->GetXaxis()->SetTitle("Tile (tiler)");
			amp2TilerHist->GetYaxis()->SetTitle("Amplitude (amp_2)");
			amp2TilerHist->SetStats(0);
			if (Constants::DO_PLOT_TREE){
				TString myCanvasName = TString::Format("%s-ch:tile-amp:tile", Constants::TREE_NAME);
				TString myCanvasTitle = TString::Format("TTree \"%s\". File \"%s\"", Constants::TREE_NAME, argv[i]);
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
				pad3->SetLeftMargin(0.15);
				pad3->SetRightMargin(0.15);
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
			}

			if (Constants::DO_PLOT_PROFILES){
				// Prepare histograms for the sliced spectra
				TH1* pmt1Hist = new TH1F("pmt1Hist", "PMT1 histogram", 2100, -1000, 20000);
				TH1* pmt2Hist = new TH1F("pmt2Hist", "PMT2 histogram", 2100, -1000, 20000);

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

					if (*tilel == Constants::TILE_PROFILE && *tiler > 0){ // tilel, ch_1 && tiler !=0
						Int_t bin = pmt1Hist->GetXaxis()->FindBin(*ch_1);
						if (bin >= 1 && bin <= pmt1Hist->GetNbinsX()){
							Int_t content = pmt1Hist->GetBinContent(bin);
							pmt1Hist->SetBinContent(bin, ++content);
						}
					}
					if (*tiler == Constants::TILE_PROFILE){
						Int_t bin = pmt2Hist->GetXaxis()->FindBin(*ch_2);
						if (bin >= 1 && bin <= pmt2Hist->GetNbinsX()){
							Int_t content = pmt2Hist->GetBinContent(bin);
							pmt2Hist->SetBinContent(bin, ++content);
						}
					}
				}

				// Plot PMT profile spectra
				TString pmtsCanvasTitle = TString::Format("Profile of the PMT spectra (tile = %d)", Constants::TILE_PROFILE);
				TCanvas* pmtsCanvas = new TCanvas("pmtsCanvas", pmtsCanvasTitle, 1280, 800);
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
