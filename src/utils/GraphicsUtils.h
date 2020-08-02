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

class GraphicsUtils {
public:
	GraphicsUtils();
	virtual ~GraphicsUtils();

	static void setMyStatsDisplay(TH1*, TVirtualPad*);
	static void alignStats(TH1*, TVirtualPad*);
	static void showFitParametersInStats(TH1*, TVirtualPad*);
};

#endif /* SRC_HELPER_GRAPHICSUTILS_H_ */
