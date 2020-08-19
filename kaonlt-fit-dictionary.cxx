// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME kaonltmIfitmIdictionary
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "src/helper/TF1Normalize.h"
#include "src/helper/TreeHelper.h"
#include "src/utils/RootUtils.h"
#include "src/utils/TreeUtils.h"
#include "src/utils/HistUtils.h"
#include "src/utils/StringUtils.h"
#include "src/utils/MathematicaAliases.h"
#include "src/utils/FitUtils.h"
#include "src/utils/GraphicsUtils.h"
#include "src/utils/TestSpectrum.h"
#include "src/model/Constants.h"
#include "src/model/FitParameters.h"
#include "src/fit/SpectrumSimplified.h"
#include "src/fit/FuncSRealNoTerm0.h"
#include "src/fit/FuncSRealFFT.h"
#include "src/fit/SpectrumReal.h"
#include "src/fit/components/AbsFunc.h"
#include "src/fit/components/FuncTermN.h"
#include "src/fit/components/FuncTerm0.h"
#include "src/fit/components/FuncB.h"
#include "src/fit/components/FuncSIdealN.h"
#include "src/fit/components/FuncSIdealNShiftedQ0.h"
#include "src/fit/AbsComponentFunc.h"
#include "src/fit/FuncSReal.h"
#include "src/fit/FuncSRealFFTNoTerm0.h"
#include "src/roofit/ExpPdf.h"
#include "src/roofit/GaussPdf.h"
#include "src/roofit/Term0Pdf.h"
#include "src/roofit/SRealNPdf.h"
#include "src/roofit/SIdealNPdf.h"
#include "src/roofit/BPdf.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_ExpPdf(void *p = 0);
   static void *newArray_ExpPdf(Long_t size, void *p);
   static void delete_ExpPdf(void *p);
   static void deleteArray_ExpPdf(void *p);
   static void destruct_ExpPdf(void *p);
   static void streamer_ExpPdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ExpPdf*)
   {
      ::ExpPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ExpPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ExpPdf", ::ExpPdf::Class_Version(), "src/roofit/ExpPdf.h", 22,
                  typeid(::ExpPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ExpPdf::Dictionary, isa_proxy, 16,
                  sizeof(::ExpPdf) );
      instance.SetNew(&new_ExpPdf);
      instance.SetNewArray(&newArray_ExpPdf);
      instance.SetDelete(&delete_ExpPdf);
      instance.SetDeleteArray(&deleteArray_ExpPdf);
      instance.SetDestructor(&destruct_ExpPdf);
      instance.SetStreamerFunc(&streamer_ExpPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ExpPdf*)
   {
      return GenerateInitInstanceLocal((::ExpPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ExpPdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_GaussPdf(void *p = 0);
   static void *newArray_GaussPdf(Long_t size, void *p);
   static void delete_GaussPdf(void *p);
   static void deleteArray_GaussPdf(void *p);
   static void destruct_GaussPdf(void *p);
   static void streamer_GaussPdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GaussPdf*)
   {
      ::GaussPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GaussPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GaussPdf", ::GaussPdf::Class_Version(), "src/roofit/GaussPdf.h", 22,
                  typeid(::GaussPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::GaussPdf::Dictionary, isa_proxy, 16,
                  sizeof(::GaussPdf) );
      instance.SetNew(&new_GaussPdf);
      instance.SetNewArray(&newArray_GaussPdf);
      instance.SetDelete(&delete_GaussPdf);
      instance.SetDeleteArray(&deleteArray_GaussPdf);
      instance.SetDestructor(&destruct_GaussPdf);
      instance.SetStreamerFunc(&streamer_GaussPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GaussPdf*)
   {
      return GenerateInitInstanceLocal((::GaussPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::GaussPdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Term0Pdf(void *p = 0);
   static void *newArray_Term0Pdf(Long_t size, void *p);
   static void delete_Term0Pdf(void *p);
   static void deleteArray_Term0Pdf(void *p);
   static void destruct_Term0Pdf(void *p);
   static void streamer_Term0Pdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Term0Pdf*)
   {
      ::Term0Pdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Term0Pdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Term0Pdf", ::Term0Pdf::Class_Version(), "src/roofit/Term0Pdf.h", 22,
                  typeid(::Term0Pdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Term0Pdf::Dictionary, isa_proxy, 16,
                  sizeof(::Term0Pdf) );
      instance.SetNew(&new_Term0Pdf);
      instance.SetNewArray(&newArray_Term0Pdf);
      instance.SetDelete(&delete_Term0Pdf);
      instance.SetDeleteArray(&deleteArray_Term0Pdf);
      instance.SetDestructor(&destruct_Term0Pdf);
      instance.SetStreamerFunc(&streamer_Term0Pdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Term0Pdf*)
   {
      return GenerateInitInstanceLocal((::Term0Pdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Term0Pdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SRealNPdf(void *p = 0);
   static void *newArray_SRealNPdf(Long_t size, void *p);
   static void delete_SRealNPdf(void *p);
   static void deleteArray_SRealNPdf(void *p);
   static void destruct_SRealNPdf(void *p);
   static void streamer_SRealNPdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SRealNPdf*)
   {
      ::SRealNPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SRealNPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SRealNPdf", ::SRealNPdf::Class_Version(), "src/roofit/SRealNPdf.h", 22,
                  typeid(::SRealNPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SRealNPdf::Dictionary, isa_proxy, 16,
                  sizeof(::SRealNPdf) );
      instance.SetNew(&new_SRealNPdf);
      instance.SetNewArray(&newArray_SRealNPdf);
      instance.SetDelete(&delete_SRealNPdf);
      instance.SetDeleteArray(&deleteArray_SRealNPdf);
      instance.SetDestructor(&destruct_SRealNPdf);
      instance.SetStreamerFunc(&streamer_SRealNPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SRealNPdf*)
   {
      return GenerateInitInstanceLocal((::SRealNPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SRealNPdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SIdealNPdf(void *p = 0);
   static void *newArray_SIdealNPdf(Long_t size, void *p);
   static void delete_SIdealNPdf(void *p);
   static void deleteArray_SIdealNPdf(void *p);
   static void destruct_SIdealNPdf(void *p);
   static void streamer_SIdealNPdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SIdealNPdf*)
   {
      ::SIdealNPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SIdealNPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SIdealNPdf", ::SIdealNPdf::Class_Version(), "src/roofit/SIdealNPdf.h", 22,
                  typeid(::SIdealNPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SIdealNPdf::Dictionary, isa_proxy, 16,
                  sizeof(::SIdealNPdf) );
      instance.SetNew(&new_SIdealNPdf);
      instance.SetNewArray(&newArray_SIdealNPdf);
      instance.SetDelete(&delete_SIdealNPdf);
      instance.SetDeleteArray(&deleteArray_SIdealNPdf);
      instance.SetDestructor(&destruct_SIdealNPdf);
      instance.SetStreamerFunc(&streamer_SIdealNPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SIdealNPdf*)
   {
      return GenerateInitInstanceLocal((::SIdealNPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SIdealNPdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_BPdf(void *p = 0);
   static void *newArray_BPdf(Long_t size, void *p);
   static void delete_BPdf(void *p);
   static void deleteArray_BPdf(void *p);
   static void destruct_BPdf(void *p);
   static void streamer_BPdf(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BPdf*)
   {
      ::BPdf *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::BPdf >(0);
      static ::ROOT::TGenericClassInfo 
         instance("BPdf", ::BPdf::Class_Version(), "src/roofit/BPdf.h", 22,
                  typeid(::BPdf), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::BPdf::Dictionary, isa_proxy, 16,
                  sizeof(::BPdf) );
      instance.SetNew(&new_BPdf);
      instance.SetNewArray(&newArray_BPdf);
      instance.SetDelete(&delete_BPdf);
      instance.SetDeleteArray(&deleteArray_BPdf);
      instance.SetDestructor(&destruct_BPdf);
      instance.SetStreamerFunc(&streamer_BPdf);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BPdf*)
   {
      return GenerateInitInstanceLocal((::BPdf*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BPdf*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ExpPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ExpPdf::Class_Name()
{
   return "ExpPdf";
}

//______________________________________________________________________________
const char *ExpPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExpPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ExpPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ExpPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ExpPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExpPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ExpPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ExpPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr GaussPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GaussPdf::Class_Name()
{
   return "GaussPdf";
}

//______________________________________________________________________________
const char *GaussPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GaussPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GaussPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GaussPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GaussPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GaussPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GaussPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GaussPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Term0Pdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Term0Pdf::Class_Name()
{
   return "Term0Pdf";
}

//______________________________________________________________________________
const char *Term0Pdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Term0Pdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Term0Pdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Term0Pdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Term0Pdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Term0Pdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Term0Pdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Term0Pdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SRealNPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SRealNPdf::Class_Name()
{
   return "SRealNPdf";
}

//______________________________________________________________________________
const char *SRealNPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRealNPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SRealNPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SRealNPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SRealNPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRealNPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SRealNPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SRealNPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SIdealNPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SIdealNPdf::Class_Name()
{
   return "SIdealNPdf";
}

//______________________________________________________________________________
const char *SIdealNPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SIdealNPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SIdealNPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SIdealNPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SIdealNPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SIdealNPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SIdealNPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SIdealNPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr BPdf::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *BPdf::Class_Name()
{
   return "BPdf";
}

//______________________________________________________________________________
const char *BPdf::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BPdf*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int BPdf::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::BPdf*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *BPdf::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BPdf*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *BPdf::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::BPdf*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ExpPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class ExpPdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      a.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, ExpPdf::IsA());
   } else {
      R__c = R__b.WriteVersion(ExpPdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      a.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ExpPdf(void *p) {
      return  p ? new(p) ::ExpPdf : new ::ExpPdf;
   }
   static void *newArray_ExpPdf(Long_t nElements, void *p) {
      return p ? new(p) ::ExpPdf[nElements] : new ::ExpPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_ExpPdf(void *p) {
      delete ((::ExpPdf*)p);
   }
   static void deleteArray_ExpPdf(void *p) {
      delete [] ((::ExpPdf*)p);
   }
   static void destruct_ExpPdf(void *p) {
      typedef ::ExpPdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_ExpPdf(TBuffer &buf, void *obj) {
      ((::ExpPdf*)obj)->::ExpPdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::ExpPdf

//______________________________________________________________________________
void GaussPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class GaussPdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, GaussPdf::IsA());
   } else {
      R__c = R__b.WriteVersion(GaussPdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GaussPdf(void *p) {
      return  p ? new(p) ::GaussPdf : new ::GaussPdf;
   }
   static void *newArray_GaussPdf(Long_t nElements, void *p) {
      return p ? new(p) ::GaussPdf[nElements] : new ::GaussPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_GaussPdf(void *p) {
      delete ((::GaussPdf*)p);
   }
   static void deleteArray_GaussPdf(void *p) {
      delete [] ((::GaussPdf*)p);
   }
   static void destruct_GaussPdf(void *p) {
      typedef ::GaussPdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_GaussPdf(TBuffer &buf, void *obj) {
      ((::GaussPdf*)obj)->::GaussPdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::GaussPdf

//______________________________________________________________________________
void Term0Pdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class Term0Pdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, Term0Pdf::IsA());
   } else {
      R__c = R__b.WriteVersion(Term0Pdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Term0Pdf(void *p) {
      return  p ? new(p) ::Term0Pdf : new ::Term0Pdf;
   }
   static void *newArray_Term0Pdf(Long_t nElements, void *p) {
      return p ? new(p) ::Term0Pdf[nElements] : new ::Term0Pdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_Term0Pdf(void *p) {
      delete ((::Term0Pdf*)p);
   }
   static void deleteArray_Term0Pdf(void *p) {
      delete [] ((::Term0Pdf*)p);
   }
   static void destruct_Term0Pdf(void *p) {
      typedef ::Term0Pdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Term0Pdf(TBuffer &buf, void *obj) {
      ((::Term0Pdf*)obj)->::Term0Pdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::Term0Pdf

//______________________________________________________________________________
void SRealNPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class SRealNPdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      Q1.Streamer(R__b);
      s1.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      mu.Streamer(R__b);
      n.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, SRealNPdf::IsA());
   } else {
      R__c = R__b.WriteVersion(SRealNPdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      Q1.Streamer(R__b);
      s1.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      mu.Streamer(R__b);
      n.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SRealNPdf(void *p) {
      return  p ? new(p) ::SRealNPdf : new ::SRealNPdf;
   }
   static void *newArray_SRealNPdf(Long_t nElements, void *p) {
      return p ? new(p) ::SRealNPdf[nElements] : new ::SRealNPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_SRealNPdf(void *p) {
      delete ((::SRealNPdf*)p);
   }
   static void deleteArray_SRealNPdf(void *p) {
      delete [] ((::SRealNPdf*)p);
   }
   static void destruct_SRealNPdf(void *p) {
      typedef ::SRealNPdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SRealNPdf(TBuffer &buf, void *obj) {
      ((::SRealNPdf*)obj)->::SRealNPdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::SRealNPdf

//______________________________________________________________________________
void SIdealNPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class SIdealNPdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q1.Streamer(R__b);
      s1.Streamer(R__b);
      n.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, SIdealNPdf::IsA());
   } else {
      R__c = R__b.WriteVersion(SIdealNPdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q1.Streamer(R__b);
      s1.Streamer(R__b);
      n.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SIdealNPdf(void *p) {
      return  p ? new(p) ::SIdealNPdf : new ::SIdealNPdf;
   }
   static void *newArray_SIdealNPdf(Long_t nElements, void *p) {
      return p ? new(p) ::SIdealNPdf[nElements] : new ::SIdealNPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_SIdealNPdf(void *p) {
      delete ((::SIdealNPdf*)p);
   }
   static void deleteArray_SIdealNPdf(void *p) {
      delete [] ((::SIdealNPdf*)p);
   }
   static void destruct_SIdealNPdf(void *p) {
      typedef ::SIdealNPdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SIdealNPdf(TBuffer &buf, void *obj) {
      ((::SIdealNPdf*)obj)->::SIdealNPdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::SIdealNPdf

//______________________________________________________________________________
void BPdf::Streamer(TBuffer &R__b)
{
   // Stream an object of class BPdf.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, BPdf::IsA());
   } else {
      R__c = R__b.WriteVersion(BPdf::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      Q0.Streamer(R__b);
      s0.Streamer(R__b);
      w.Streamer(R__b);
      a.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_BPdf(void *p) {
      return  p ? new(p) ::BPdf : new ::BPdf;
   }
   static void *newArray_BPdf(Long_t nElements, void *p) {
      return p ? new(p) ::BPdf[nElements] : new ::BPdf[nElements];
   }
   // Wrapper around operator delete
   static void delete_BPdf(void *p) {
      delete ((::BPdf*)p);
   }
   static void deleteArray_BPdf(void *p) {
      delete [] ((::BPdf*)p);
   }
   static void destruct_BPdf(void *p) {
      typedef ::BPdf current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_BPdf(TBuffer &buf, void *obj) {
      ((::BPdf*)obj)->::BPdf::Streamer(buf);
   }
} // end of namespace ROOT for class ::BPdf

namespace {
  void TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl() {
    static const char* headers[] = {
"src/helper/TF1Normalize.h",
"src/helper/TreeHelper.h",
"src/utils/RootUtils.h",
"src/utils/TreeUtils.h",
"src/utils/HistUtils.h",
"src/utils/StringUtils.h",
"src/utils/MathematicaAliases.h",
"src/utils/FitUtils.h",
"src/utils/GraphicsUtils.h",
"src/utils/TestSpectrum.h",
"src/model/Constants.h",
"src/model/FitParameters.h",
"src/fit/SpectrumSimplified.h",
"src/fit/FuncSRealNoTerm0.h",
"src/fit/FuncSRealFFT.h",
"src/fit/SpectrumReal.h",
"src/fit/components/AbsFunc.h",
"src/fit/components/FuncTermN.h",
"src/fit/components/FuncTerm0.h",
"src/fit/components/FuncB.h",
"src/fit/components/FuncSIdealN.h",
"src/fit/components/FuncSIdealNShiftedQ0.h",
"src/fit/AbsComponentFunc.h",
"src/fit/FuncSReal.h",
"src/fit/FuncSRealFFTNoTerm0.h",
"src/roofit/ExpPdf.h",
"src/roofit/GaussPdf.h",
"src/roofit/Term0Pdf.h",
"src/roofit/SRealNPdf.h",
"src/roofit/SIdealNPdf.h",
"src/roofit/BPdf.h",
0
    };
    static const char* includePaths[] = {
"/home/petrstepanov/Applications/root-6.22.00/include/",
"/home/petrstepanov/Development/kaonlt-fit/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "kaonltmIfitmIdictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$src/roofit/ExpPdf.h")))  ExpPdf;
class __attribute__((annotate("$clingAutoload$src/roofit/GaussPdf.h")))  GaussPdf;
class __attribute__((annotate("$clingAutoload$src/roofit/Term0Pdf.h")))  Term0Pdf;
class __attribute__((annotate("$clingAutoload$src/roofit/SRealNPdf.h")))  SRealNPdf;
class __attribute__((annotate("$clingAutoload$src/roofit/SIdealNPdf.h")))  SIdealNPdf;
class __attribute__((annotate("$clingAutoload$src/roofit/BPdf.h")))  BPdf;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "kaonltmIfitmIdictionary dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/helper/TF1Normalize.h"
#include "src/helper/TreeHelper.h"
#include "src/utils/RootUtils.h"
#include "src/utils/TreeUtils.h"
#include "src/utils/HistUtils.h"
#include "src/utils/StringUtils.h"
#include "src/utils/MathematicaAliases.h"
#include "src/utils/FitUtils.h"
#include "src/utils/GraphicsUtils.h"
#include "src/utils/TestSpectrum.h"
#include "src/model/Constants.h"
#include "src/model/FitParameters.h"
#include "src/fit/SpectrumSimplified.h"
#include "src/fit/FuncSRealNoTerm0.h"
#include "src/fit/FuncSRealFFT.h"
#include "src/fit/SpectrumReal.h"
#include "src/fit/components/AbsFunc.h"
#include "src/fit/components/FuncTermN.h"
#include "src/fit/components/FuncTerm0.h"
#include "src/fit/components/FuncB.h"
#include "src/fit/components/FuncSIdealN.h"
#include "src/fit/components/FuncSIdealNShiftedQ0.h"
#include "src/fit/AbsComponentFunc.h"
#include "src/fit/FuncSReal.h"
#include "src/fit/FuncSRealFFTNoTerm0.h"
#include "src/roofit/ExpPdf.h"
#include "src/roofit/GaussPdf.h"
#include "src/roofit/Term0Pdf.h"
#include "src/roofit/SRealNPdf.h"
#include "src/roofit/SIdealNPdf.h"
#include "src/roofit/BPdf.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"BPdf", payloadCode, "@",
"ExpPdf", payloadCode, "@",
"GaussPdf", payloadCode, "@",
"SIdealNPdf", payloadCode, "@",
"SRealNPdf", payloadCode, "@",
"Term0Pdf", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("kaonlt-fit-dictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_kaonltmIfitmIdictionary() {
  TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl();
}
