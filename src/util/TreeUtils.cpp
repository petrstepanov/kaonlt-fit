/*
 * TreeUtils.cpp
 *
 *  Created on: Jul 28, 2020
 *      Author: petrstepanov
 */

#include "TreeUtils.h"
#include "TVirtualTreePlayer.h"
#include "TCanvas.h"
#include "TSystem.h"

TreeUtils::TreeUtils() {
	// TODO Auto-generated constructor stub

}

TreeUtils::~TreeUtils() {
	// TODO Auto-generated destructor stub
}

TH1* TreeUtils::GetBranchHistogram(TTree* tree, const char* branchName, const char* histName){
	// Create 1D histogram from the tree branch
	// Copied code from TTree::Draw()
	TVirtualTreePlayer* treePlayer = tree->GetPlayer();
	// ROOT TBrowser() does following command in Terminal (use up arrow in Terminal after plotting): tv__tree->Draw("tilel","","", 23458364, 0);
	// I've noticed the 3rd parameter is number of (tree entries -2): 23458364 = 23458366 - 2
	TString tempCanvasName = TString::Format("%s_temp_canvas", branchName);
	TCanvas* tempCanvas = new TCanvas(tempCanvasName);
	treePlayer->DrawSelect(branchName,"","", tree->GetEntries() - 2, 0);

	TH1* hist = (TH1*)(treePlayer->GetHistogram()->Clone(histName));
	// Set Directory to 0: https://root.cern.ch/root/roottalk/roottalk99/1796.html
	hist->SetDirectory(0);

	// Close and delete temporary canvas
	// https://root-forum.cern.ch/t/how-to-close-or-delete-a-canvas-inside-a-macro/23619/3
	tempCanvas->Close();
	// gSystem->ProcessEvents();
	//delete tempCanvas;
	//tempCanvas = 0;

	return hist;
}
