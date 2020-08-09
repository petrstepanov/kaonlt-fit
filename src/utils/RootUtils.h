/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   RootUtils.h
 * Author: petrstepanov
 *
 * Created on August 24, 2017, 8:16 PM
 */

#ifndef RootUtils_H
#define RootUtils_H

#include <TROOT.h>
#include <TStopwatch.h>
#include <TGFrame.h>
#include <TGNumberEntry.h>
#include <TRandom.h>
#include <RooRealVar.h>
#include <RooAbsPdf.h>

class RootUtils {
public:
    static void deleteObject(const char* name);
    static void deleteObject(TObject* obj);
    static Int_t getNumCpu();
    static void startTimer(void);
    static void stopAndPrintTimer();

private:
    static TStopwatch* watch;
};

#endif /* RootUtils_H */

