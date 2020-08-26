/*
 * TestSpectrum.cpp
 *
 *  Created on: Aug 4, 2020
 *      Author: petrstepanov
 */

#include "TestSpectrum.h"
#include <iostream>
#include <vector>
#include <TH1I.h>
#include "../utils/FitUtils.h"
#include "../fit/FuncSReal.h"
#include "../fit/FuncSRealNoTerm0.h"

TestSpectrum::TestSpectrum(){};
TestSpectrum::~TestSpectrum(){};

//TestSpectrum* TestSpectrum::instance = NULL;
//
//TestSpectrum* TestSpectrum::getInstance(){
//    if (!instance){
//        instance = new TestSpectrum;
//    }
//    return instance;
//}

// Original digitized histogram
Int_t TestSpectrum::array[] = {2, 2, 0, 0, 0, 0, 0, 7, 2, 1, 1, 0, 2, 1, 1, 7, 2, 1, 2, 7, 21, 700, 800, 750, 150, 160, 152, 176, 163, 173, 173, 168, 166, 197, 191, 200, 184, 216, 245, 234, 320, 290, 277, 302, 343, 390, 408, 454, 478, 485, 514, 609, 522, 602, 612, 640, 636, 677, 610, 630, 670, 695, 694, 685, 656, 688, 633, 572, 601, 607, 602, 566, 546, 514, 555, 532, 495, 470, 515, 485, 491, 485, 491, 480, 468, 509, 470, 491, 508, 471, 519, 492, 491, 484, 490, 495, 488, 513, 481, 479, 480, 491, 459, 491, 485, 490, 454, 455, 393, 457, 421, 416, 437, 438, 424, 376, 397, 383, 398, 384, 341, 380, 360, 368, 356, 331, 358, 316, 311, 331, 286, 315, 312, 287, 342, 297, 307, 284, 259, 283, 295, 260, 250, 281, 261, 253, 235, 230, 227, 259, 240, 241, 212, 186, 203, 185, 210, 187, 183, 202, 189, 169, 175, 194, 174, 160, 182, 153, 154, 170, 188, 167, 135, 148, 135, 155, 149, 143, 138, 130, 121, 142, 115, 103, 96, 113, 92, 95, 84, 106, 95, 86, 93, 80, 109, 80, 89, 76, 87, 72, 65, 68, 65, 62, 80, 63, 53, 63, 65, 61, 58, 57, 61, 42, 45, 54, 47, 45, 46, 45, 42, 48, 37, 39, 42, 36, 40, 37, 23, 39, 28, 33, 27, 32, 26, 33, 42, 26, 31, 32, 35, 22, 21, 25, 29, 28, 21, 20, 24, 20, 19, 11, 15, 26, 18, 17, 11, 20, 15, 8, 15, 18, 13, 12, 15, 10, 9, 10, 12, 13, 14, 9, 8, 5, 9, 15, 8, 6, 8, 5, 14, 7, 3, 7, 5, 4, 9, 4, 3, 8, 5, 5, 7, 6};

// Corrected histogram by the generated from function
Int_t TestSpectrum::array2[] = {2, 2, 0, 0, 0, 0, 0, 7, 2, 1, 1, 0, 2, 1, 1, 7, 2, 1, 2, 7, 21, 580, 6249, 163, 150, 160, 152, 176, 163, 173, 173, 168, 166, 197, 191, 200, 184, 216, 245, 234, 320, 290, 277, 302, 343, 390, 408, 454, 478, 485, 514, 609, 522, 602, 612, 640, 636, 677, 610, 630, 670, 695, 694, 685, 656, 688, 633, 572, 601, 607, 602, 566, 546, 514, 555, 532, 495, 470, 515, 485, 491, 485, 491, 480, 468, 509, 470, 491, 508, 471, 519, 492, 491, 484, 490, 495, 488, 513, 481, 479, 480, 491, 459, 491, 485, 490, 454, 455, 393, 457, 421, 416, 437, 438, 424, 376, 397, 383, 398, 384, 341, 380, 360, 368, 356, 331, 358, 316, 311, 331, 286, 315, 312, 287, 342, 297, 307, 284, 259, 283, 295, 260, 250, 281, 261, 253, 235, 230, 227, 259, 240, 241, 212, 186, 203, 185, 210, 187, 183, 202, 189, 169, 175, 194, 174, 160, 182, 153, 154, 170, 188, 167, 135, 148, 135, 155, 149, 143, 138, 130, 121, 142, 115, 103, 96, 113, 92, 95, 84, 106, 95, 86, 93, 80, 109, 80, 89, 76, 87, 72, 65, 68, 65, 62, 80, 63, 53, 63, 65, 61, 58, 57, 61, 42, 45, 54, 47, 45, 46, 45, 42, 48, 37, 39, 42, 36, 40, 37, 23, 39, 28, 33, 27, 32, 26, 33, 42, 26, 31, 32, 35, 22, 21, 25, 29, 28, 21, 20, 24, 20, 19, 11, 15, 26, 18, 17, 11, 20, 15, 8, 15, 18, 13, 12, 15, 10, 9, 10, 12, 13, 14, 9, 8, 5, 9, 15, 8, 6, 8, 5, 14, 7, 3, 7, 5, 4, 9, 4, 3, 8, 5, 5, 7, 6};

// Corrected histogram without term 0
Int_t TestSpectrum::array3[] = {2, 2, 0, 0, 0, 0, 0, 7, 2, 1, 1, 0, 2, 1, 1, 7, 2, 1, 2, 7, 11, 15, 20, 25, 30, 35, 45, 55, 65, 85, 105, 125, 145, 165, 185, 200, 184, 216, 245, 234, 320, 290, 277, 302, 343, 390, 408, 454, 478, 485, 514, 609, 522, 602, 612, 640, 636, 677, 610, 630, 670, 695, 694, 685, 656, 688, 633, 572, 601, 607, 602, 566, 546, 514, 555, 532, 495, 470, 515, 485, 491, 485, 491, 480, 468, 509, 470, 491, 508, 471, 519, 492, 491, 484, 490, 495, 488, 513, 481, 479, 480, 491, 459, 491, 485, 490, 454, 455, 393, 457, 421, 416, 437, 438, 424, 376, 397, 383, 398, 384, 341, 380, 360, 368, 356, 331, 358, 316, 311, 331, 286, 315, 312, 287, 342, 297, 307, 284, 259, 283, 295, 260, 250, 281, 261, 253, 235, 230, 227, 259, 240, 241, 212, 186, 203, 185, 210, 187, 183, 202, 189, 169, 175, 194, 174, 160, 182, 153, 154, 170, 188, 167, 135, 148, 135, 155, 149, 143, 138, 130, 121, 142, 115, 103, 96, 113, 92, 95, 84, 106, 95, 86, 93, 80, 109, 80, 89, 76, 87, 72, 65, 68, 65, 62, 80, 63, 53, 63, 65, 61, 58, 57, 61, 42, 45, 54, 47, 45, 46, 45, 42, 48, 37, 39, 42, 36, 40, 37, 23, 39, 28, 33, 27, 32, 26, 33, 42, 26, 31, 32, 35, 22, 21, 25, 29, 28, 21, 20, 24, 20, 19, 11, 15, 26, 18, 17, 11, 20, 15, 8, 15, 18, 13, 12, 15, 10, 9, 10, 12, 13, 14, 9, 8, 5, 9, 15, 8, 6, 8, 5, 14, 7, 3, 7, 5, 4, 9, 4, 3, 8, 5, 5, 7, 6};

TH1* TestSpectrum::getHistogramPaper(){
	std::vector<Int_t> vector (array, array + sizeof(array) / sizeof(array[0]) );
	TH1* hist = new TH1I("bellamyHistDigitized", "Bellamy histogram. Digitized from figure.", (Int_t)vector.size(), 0, (Int_t)vector.size());
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");

	Int_t bin = 0;
	for (int count : vector) {
		hist->SetBinContent(++bin, count);
	}
	return hist;
}

TH1* TestSpectrum::getHistogramPaperFix(){
	std::vector<Int_t> vector (array2, array2 + sizeof(array2) / sizeof(array2[0]) );
	TH1* hist = new TH1I("bellamyHistDigitizedFix", "Bellamy histogram. Digitized from figure.", (Int_t)vector.size(), 0, (Int_t)vector.size());
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");

	Int_t bin = 0;
	for (int count : vector) {
		hist->SetBinContent(++bin, count);
	}
	return hist;
}

TH1* TestSpectrum::getHistogramPaperNoTerm0(){
	std::vector<Int_t> vector (array3, array3 + sizeof(array3) / sizeof(array3[0]) );
	TH1* hist = new TH1I("bellamyHistDigitizedNoTerm0", "Bellamy histogram with cut Term0. Digitized from figure.", (Int_t)vector.size(), 0, (Int_t)vector.size());
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");

	Int_t bin = 0;
	for (int count : vector) {
		hist->SetBinContent(++bin, count);
	}
	return hist;
}

TH1* TestSpectrum::getHistogramGenerated(FitParameters* parameters){
	Int_t nBins = sizeof(array) / sizeof(array[0]);
	TH1F *hist = new TH1F("histBellamy", "Bellamy histogram. Random fill from fit function.", nBins, 0, nBins);
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");
	FuncSReal* funcObj = new FuncSReal(hist);
	FitUtils::fillHistogramFromFuncObject(hist, parameters, funcObj);
	return hist;
}

TH1* TestSpectrum::getHistogramGeneratedNoTerm0(FitParameters* parameters){
	Int_t nBins = sizeof(array) / sizeof(array[0]);
	TH1F *hist = new TH1F("histBellamyNoTerm0", "Bellamy histogram without Term0. Random fill from fit function.", nBins, 0, nBins);
	hist->GetXaxis()->SetTitle("ADC Channel");
	hist->GetYaxis()->SetTitle("Events");
	FuncSRealNoTerm0* funcObj = new FuncSRealNoTerm0(hist);
	FitUtils::fillHistogramFromFuncObject(hist, parameters, funcObj);
	return hist;
}
