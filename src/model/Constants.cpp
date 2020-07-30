/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Constants.cpp
 * Author: petrstepanov
 *
 * Created on October 29, 2017, 7:34 PM
 */

// Disable warnings for -Wwrite-strings
// https://stackoverflow.com/questions/925179/selectively-remove-warning-message-gcc

#include "Constants.h"

const char* Constants::APPLICATION_NAME = "KaonLT Fit";

const char* Constants::TREE_NAME = "tree1;2";
const UInt_t Constants::TILE_PROFILE = 60;

const Bool_t Constants::DO_PLOT_TREE = kTRUE;
const Bool_t Constants::DO_PLOT_PROFILES = kFALSE;

const std::string Constants::drawOptions[] = { "SURF2", "LEGO2" };
