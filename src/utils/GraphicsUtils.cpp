/*
 * GraphicsUtils.cpp
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#include <TPaveStats.h>
#include "../utils/GraphicsUtils.h"

GraphicsUtils::GraphicsUtils() {
	// TODO Auto-generated constructor stub

}

GraphicsUtils::~GraphicsUtils() {
	// TODO Auto-generated destructor stub
}

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
	pad->Modified();
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	Double_t statsWidth = stats->GetX2NDC() - stats->GetX1NDC();
	Double_t statsHeight = stats->GetY2NDC() - stats->GetY1NDC();
	// Move stats horizontally
	stats->SetX2NDC(0.9);
	stats->SetX1NDC(stats->GetX2NDC() - statsWidth);
	// Move stats vertically
	stats->SetY2NDC(0.9);
	stats->SetY1NDC(stats->GetY2NDC() - statsHeight);
	// Display only histogram entries
	pad->Modified();
	pad->Update();
}

void GraphicsUtils::showFitParametersInStats(TH1* hist, TVirtualPad* pad){
	pad->Modified();
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	stats->SetOptFit(1011);
	pad->Modified();
	pad->Update();
}
