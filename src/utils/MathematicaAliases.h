#ifndef SRC_M_H_
#define SRC_M_H_

#include <RtypesCore.h>
#include <TMath.h>

// Alias functions for the Mathematica cform[%] command
Double_t Sqrt(Double_t x);

Double_t Power(Double_t x, Double_t y);

Double_t Factorial(Int_t n);

Int_t UnitStep(Double_t x);

Double_t Erf(Double_t x);

Double_t Abs(Double_t x);

Double_t Sign(Double_t x);

// Constants
extern Double_t E;
extern Double_t Pi;

#endif /* SRC_M_H_ */
