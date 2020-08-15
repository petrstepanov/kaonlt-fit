/*
 * GraphicsUtils.h
 *
 *  Created on: Jul 30, 2020
 *      Author: petrstepanov
 */

#ifndef SRC_HELPER_GraphicsUtils_H_
#define SRC_HELPER_GraphicsUtils_H_

#include <TH1.h>
#include <TVirtualPad.h>
#include <TFitResult.h>
#include <TPaveText.h>
#include <TFitResultPtr.h>
#include <vector>

struct Margin {
	Double_t left;
	Double_t right;
	Double_t bottom;
	Double_t top;
};

class GraphicsUtils {
public:
	GraphicsUtils();
	virtual ~GraphicsUtils();

	static const Double_t TEXT_SIZE_NORMAL;
	static const Double_t TEXT_SIZE_SMALL;
	static const Double_t TEXT_SIZE_SMALLER;

	static const Double_t LINE_HEIGHT_NORMAL;
	static const Double_t LINE_HEIGHT_SMALL;

	static const Int_t FONT_REGULAR;
	static const Int_t FONT_BOLD;

	static const Double_t TOP_TO_BOTTOM_PAD_HEIGHT_RATIO;

	static const Margin padMargins;

    static const std::vector<Int_t> colorSet;

	static Style_t getFontCode(Int_t fontSize);
	static Double_t getFontSizeScale(Bool_t isTopPad);

	static void setMyStatsDisplay(TH1*, TVirtualPad*);
	static void alignStats(TH1*, TVirtualPad*);
	static void stylePaveText(TPaveText* paveText, TVirtualPad* pad);
	static void setStatsFitOption(TH1*, TVirtualPad*, Int_t);
//	static void addLineToStats(TH1*, const char*, TVirtualPad*);
//	static void showChi2InStats(TH1*, TFitResultPtr, TVirtualPad*);
	static void styleAxis(TAxis* axis, const char* title, Double_t titleOffset, Double_t labelOffset, Bool_t isTopPad);

};

#endif /* SRC_HELPER_GRAPHICSUTILS_H_ */
