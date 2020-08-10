#include "MathematicaAliases.h"

// Alias functions for the Mathematica cform[%] command
Double_t Sqrt(Double_t x){
	return sqrt(x);
}

Double_t Power(Double_t x, Double_t y){
	return pow(x,y);
}

Double_t Factorial(Int_t n){
	return TMath::Factorial(n);
}

Int_t UnitStep(Double_t x){
	return (x<0)?0:1;
}

Double_t Erf(Double_t x){
	return TMath::Erf(x);
}

Double_t Abs(Double_t x){
	return TMath::Abs(x);
}

Double_t Sign(Double_t x){
	return x/TMath::Abs(x);
}

// Constants
Double_t E = TMath::E();
Double_t Pi = TMath::Pi();