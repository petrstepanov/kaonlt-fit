/*
 * GraphicsUtils.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include <TPaveStats.h>
#include <TLatex.h>
#include "../utils/GraphicsUtils.h"

GraphicsUtils::GraphicsUtils() {
}

GraphicsUtils::~GraphicsUtils() {
}

const Double_t GraphicsUtils::TEXT_SIZE_NORMAL = 0.03;
const Double_t GraphicsUtils::TEXT_SIZE_SMALL = TEXT_SIZE_NORMAL*0.75;
const Double_t GraphicsUtils::TEXT_SIZE_SMALLER = TEXT_SIZE_SMALL*0.75;

const Double_t GraphicsUtils::LINE_HEIGHT_NORMAL = 0.045;
const Double_t GraphicsUtils::LINE_HEIGHT_SMALL = LINE_HEIGHT_NORMAL*0.75;

const Int_t GraphicsUtils::FONT_REGULAR = 4;
const Int_t GraphicsUtils::FONT_BOLD = 6;

const Double_t GraphicsUtils::TOP_TO_BOTTOM_PAD_HEIGHT_RATIO = 2.5;

const Margin GraphicsUtils::padMargins = { 0.10, 0.02, 0.15, 0.05 }; // left, right, bottom, top

const std::vector<Int_t> GraphicsUtils::colorSet = { kViolet + 6, kSpring - 5, kAzure + 8,
		kPink + 1, kGray + 1, kViolet - 4, kRed - 7, kOrange};

void GraphicsUtils::setMyStatsDisplay(TH1* hist, TVirtualPad* pad){
	pad->Modified();
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	// Modify statistics display https://root.cern.ch/doc/master/classTPaveStats.html
	stats->SetOptStat(10);
	pad->Modified();
	pad->Update();
}

void GraphicsUtils::alignStats(TH1* hist, TVirtualPad* pad){
	// pad->Modified();
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	Double_t statsWidth = 0.3; //stats->GetX2NDC() - stats->GetX1NDC();
	Double_t statsHeight = 0.04*stats->GetListOfLines()->GetSize(); // stats->GetY2NDC() - stats->GetY1NDC();
	// Move stats horizontally
	stats->SetX2NDC(1 - pad->GetRightMargin());
	stats->SetX1NDC(stats->GetX2NDC() - statsWidth);
	// Move stats vertically
	stats->SetY2NDC(1 - pad->GetTopMargin());
	stats->SetY1NDC(stats->GetY2NDC() - statsHeight);
	// Display only histogram entries
	pad->Modified();
	pad->Update();
}

void GraphicsUtils::setStatsFitOption(TH1* hist, TVirtualPad* pad, Int_t fit){
	pad->Modified();
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	if (stats){
		stats->SetOptFit(fit);
	}
	pad->Modified();
	pad->Update();
}

//void GraphicsUtils::addLineToStats(TH1* hist, const char* string, TVirtualPad* pad){
//	pad->Modified();
//	pad->Update();
//	TPaveStats *stats = (TPaveStats*)pad->GetPrimitive("stats");
//	// TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
//	if (stats){
//		stats->SetName("mystats");
//		TLatex *text = new TLatex(0, 0, string);
//		// text->SetTextFont(42);
//		// text->SetTextSize(0.04);
//		stats->GetListOfLines()->Add(text);
//	}
//	// Avoid the the automatic redrawing of stats
//	hist->SetStats(0);
//	pad->Modified();
//	pad->Update();
//}
//
//void GraphicsUtils::showChi2InStats(TH1* hist, TFitResultPtr fitResultPtr, TVirtualPad* pad){
//	TString string = TString::Format("\\chi^2 = %f", fitResultPtr->Chi2());
//	addLineToStats(hist, string.Data(), pad);
//}

void GraphicsUtils::styleAxis(TAxis* axis, const char* title, Double_t titleOffset, Double_t labelOffset, Bool_t isTopPad){
    Style_t fontCode = getFontCode(FONT_REGULAR);

    axis->SetLabelFont(fontCode);
    axis->SetLabelOffset(labelOffset);
    axis->SetLabelSize(TEXT_SIZE_SMALL*getFontSizeScale(isTopPad));

    axis->SetTitleFont(fontCode);
    axis->SetTitleOffset(titleOffset);
    axis->SetTitleSize(TEXT_SIZE_NORMAL*getFontSizeScale(isTopPad));

    axis->CenterTitle(kTRUE);
    axis->SetTitle(title);
}


Style_t GraphicsUtils::getFontCode(Int_t fontNumber){
    // https://root.cern.ch/doc/master/classTAttText.html#T5
	Int_t precision = 2;  // if "1" then problems rendering
	return fontNumber * 10 + precision;
}

Double_t GraphicsUtils::getFontSizeScale(Bool_t isTopPad){
	if (isTopPad){
		Double_t scale = 1/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO+1));
		return scale;
	}
	Double_t scale = 1/(1/(TOP_TO_BOTTOM_PAD_HEIGHT_RATIO+1));
	return scale;
}
