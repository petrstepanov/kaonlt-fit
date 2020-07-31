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

void GraphicsUtils::styleLegend(TH1* hist, TVirtualPad* pad){
	pad->Update();
	TPaveStats *stats = (TPaveStats*) hist->FindObject("stats");
	stats->SetX1NDC(0.680);
	stats->SetY1NDC(0.742);
	stats->SetX2NDC(0.9);
	stats->SetY2NDC(0.9);
//	stats->SetOptStat(11);
	pad->Modified();
	pad->Update();
}
