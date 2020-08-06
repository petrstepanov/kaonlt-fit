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
#include "src/helper/TreeHelper.h"
#include "src/utils/TreeUtils.h"
#include "src/utils/HistUtils.h"
#include "src/utils/StringUtils.h"
#include "src/utils/MathematicaAliases.h"
#include "src/utils/GraphicsUtils.h"
#include "src/utils/TestSpectrum.h"
#include "src/model/Database.h"
#include "src/model/Constants.h"
#include "src/model/Model.h"
#include "src/fit/AbsFunc.h"
#include "src/fit/FuncTerm0.h"
#include "src/fit/FuncB.h"
#include "src/fit/FuncSIdealN.h"
#include "src/fit/FuncSReal.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *AbsFunc_Dictionary();
   static void AbsFunc_TClassManip(TClass*);
   static void delete_AbsFunc(void *p);
   static void deleteArray_AbsFunc(void *p);
   static void destruct_AbsFunc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AbsFunc*)
   {
      ::AbsFunc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::AbsFunc));
      static ::ROOT::TGenericClassInfo 
         instance("AbsFunc", "src/fit/AbsFunc.h", 13,
                  typeid(::AbsFunc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &AbsFunc_Dictionary, isa_proxy, 0,
                  sizeof(::AbsFunc) );
      instance.SetDelete(&delete_AbsFunc);
      instance.SetDeleteArray(&deleteArray_AbsFunc);
      instance.SetDestructor(&destruct_AbsFunc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AbsFunc*)
   {
      return GenerateInitInstanceLocal((::AbsFunc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AbsFunc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *AbsFunc_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::AbsFunc*)0x0)->GetClass();
      AbsFunc_TClassManip(theClass);
   return theClass;
   }

   static void AbsFunc_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FuncTerm0_Dictionary();
   static void FuncTerm0_TClassManip(TClass*);
   static void *new_FuncTerm0(void *p = 0);
   static void *newArray_FuncTerm0(Long_t size, void *p);
   static void delete_FuncTerm0(void *p);
   static void deleteArray_FuncTerm0(void *p);
   static void destruct_FuncTerm0(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FuncTerm0*)
   {
      ::FuncTerm0 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FuncTerm0));
      static ::ROOT::TGenericClassInfo 
         instance("FuncTerm0", "src/fit/FuncTerm0.h", 13,
                  typeid(::FuncTerm0), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FuncTerm0_Dictionary, isa_proxy, 0,
                  sizeof(::FuncTerm0) );
      instance.SetNew(&new_FuncTerm0);
      instance.SetNewArray(&newArray_FuncTerm0);
      instance.SetDelete(&delete_FuncTerm0);
      instance.SetDeleteArray(&deleteArray_FuncTerm0);
      instance.SetDestructor(&destruct_FuncTerm0);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FuncTerm0*)
   {
      return GenerateInitInstanceLocal((::FuncTerm0*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FuncTerm0*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FuncTerm0_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FuncTerm0*)0x0)->GetClass();
      FuncTerm0_TClassManip(theClass);
   return theClass;
   }

   static void FuncTerm0_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FuncB_Dictionary();
   static void FuncB_TClassManip(TClass*);
   static void *new_FuncB(void *p = 0);
   static void *newArray_FuncB(Long_t size, void *p);
   static void delete_FuncB(void *p);
   static void deleteArray_FuncB(void *p);
   static void destruct_FuncB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FuncB*)
   {
      ::FuncB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FuncB));
      static ::ROOT::TGenericClassInfo 
         instance("FuncB", "src/fit/FuncB.h", 13,
                  typeid(::FuncB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FuncB_Dictionary, isa_proxy, 0,
                  sizeof(::FuncB) );
      instance.SetNew(&new_FuncB);
      instance.SetNewArray(&newArray_FuncB);
      instance.SetDelete(&delete_FuncB);
      instance.SetDeleteArray(&deleteArray_FuncB);
      instance.SetDestructor(&destruct_FuncB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FuncB*)
   {
      return GenerateInitInstanceLocal((::FuncB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FuncB*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FuncB_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FuncB*)0x0)->GetClass();
      FuncB_TClassManip(theClass);
   return theClass;
   }

   static void FuncB_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FuncSIdealN_Dictionary();
   static void FuncSIdealN_TClassManip(TClass*);
   static void delete_FuncSIdealN(void *p);
   static void deleteArray_FuncSIdealN(void *p);
   static void destruct_FuncSIdealN(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FuncSIdealN*)
   {
      ::FuncSIdealN *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FuncSIdealN));
      static ::ROOT::TGenericClassInfo 
         instance("FuncSIdealN", "src/fit/FuncSIdealN.h", 14,
                  typeid(::FuncSIdealN), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FuncSIdealN_Dictionary, isa_proxy, 0,
                  sizeof(::FuncSIdealN) );
      instance.SetDelete(&delete_FuncSIdealN);
      instance.SetDeleteArray(&deleteArray_FuncSIdealN);
      instance.SetDestructor(&destruct_FuncSIdealN);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FuncSIdealN*)
   {
      return GenerateInitInstanceLocal((::FuncSIdealN*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FuncSIdealN*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FuncSIdealN_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FuncSIdealN*)0x0)->GetClass();
      FuncSIdealN_TClassManip(theClass);
   return theClass;
   }

   static void FuncSIdealN_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FuncSReal_Dictionary();
   static void FuncSReal_TClassManip(TClass*);
   static void delete_FuncSReal(void *p);
   static void deleteArray_FuncSReal(void *p);
   static void destruct_FuncSReal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FuncSReal*)
   {
      ::FuncSReal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FuncSReal));
      static ::ROOT::TGenericClassInfo 
         instance("FuncSReal", "src/fit/FuncSReal.h", 18,
                  typeid(::FuncSReal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FuncSReal_Dictionary, isa_proxy, 0,
                  sizeof(::FuncSReal) );
      instance.SetDelete(&delete_FuncSReal);
      instance.SetDeleteArray(&deleteArray_FuncSReal);
      instance.SetDestructor(&destruct_FuncSReal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FuncSReal*)
   {
      return GenerateInitInstanceLocal((::FuncSReal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FuncSReal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FuncSReal_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FuncSReal*)0x0)->GetClass();
      FuncSReal_TClassManip(theClass);
   return theClass;
   }

   static void FuncSReal_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_AbsFunc(void *p) {
      delete ((::AbsFunc*)p);
   }
   static void deleteArray_AbsFunc(void *p) {
      delete [] ((::AbsFunc*)p);
   }
   static void destruct_AbsFunc(void *p) {
      typedef ::AbsFunc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AbsFunc

namespace ROOT {
   // Wrappers around operator new
   static void *new_FuncTerm0(void *p) {
      return  p ? new(p) ::FuncTerm0 : new ::FuncTerm0;
   }
   static void *newArray_FuncTerm0(Long_t nElements, void *p) {
      return p ? new(p) ::FuncTerm0[nElements] : new ::FuncTerm0[nElements];
   }
   // Wrapper around operator delete
   static void delete_FuncTerm0(void *p) {
      delete ((::FuncTerm0*)p);
   }
   static void deleteArray_FuncTerm0(void *p) {
      delete [] ((::FuncTerm0*)p);
   }
   static void destruct_FuncTerm0(void *p) {
      typedef ::FuncTerm0 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FuncTerm0

namespace ROOT {
   // Wrappers around operator new
   static void *new_FuncB(void *p) {
      return  p ? new(p) ::FuncB : new ::FuncB;
   }
   static void *newArray_FuncB(Long_t nElements, void *p) {
      return p ? new(p) ::FuncB[nElements] : new ::FuncB[nElements];
   }
   // Wrapper around operator delete
   static void delete_FuncB(void *p) {
      delete ((::FuncB*)p);
   }
   static void deleteArray_FuncB(void *p) {
      delete [] ((::FuncB*)p);
   }
   static void destruct_FuncB(void *p) {
      typedef ::FuncB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FuncB

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FuncSIdealN(void *p) {
      delete ((::FuncSIdealN*)p);
   }
   static void deleteArray_FuncSIdealN(void *p) {
      delete [] ((::FuncSIdealN*)p);
   }
   static void destruct_FuncSIdealN(void *p) {
      typedef ::FuncSIdealN current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FuncSIdealN

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FuncSReal(void *p) {
      delete ((::FuncSReal*)p);
   }
   static void deleteArray_FuncSReal(void *p) {
      delete [] ((::FuncSReal*)p);
   }
   static void destruct_FuncSReal(void *p) {
      typedef ::FuncSReal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FuncSReal

namespace {
  void TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl() {
    static const char* headers[] = {
"src/helper/TreeHelper.h",
"src/utils/TreeUtils.h",
"src/utils/HistUtils.h",
"src/utils/StringUtils.h",
"src/utils/MathematicaAliases.h",
"src/utils/GraphicsUtils.h",
"src/utils/TestSpectrum.h",
"src/model/Database.h",
"src/model/Constants.h",
"src/model/Model.h",
"src/fit/AbsFunc.h",
"src/fit/FuncTerm0.h",
"src/fit/FuncB.h",
"src/fit/FuncSIdealN.h",
"src/fit/FuncSReal.h",
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
class __attribute__((annotate("$clingAutoload$src/fit/AbsFunc.h")))  AbsFunc;
class __attribute__((annotate("$clingAutoload$src/fit/FuncTerm0.h")))  FuncTerm0;
class __attribute__((annotate("$clingAutoload$src/fit/FuncB.h")))  FuncB;
class __attribute__((annotate("$clingAutoload$src/fit/FuncSIdealN.h")))  FuncSIdealN;
class __attribute__((annotate("$clingAutoload$src/fit/FuncSReal.h")))  FuncSReal;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "kaonltmIfitmIdictionary dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/helper/TreeHelper.h"
#include "src/utils/TreeUtils.h"
#include "src/utils/HistUtils.h"
#include "src/utils/StringUtils.h"
#include "src/utils/MathematicaAliases.h"
#include "src/utils/GraphicsUtils.h"
#include "src/utils/TestSpectrum.h"
#include "src/model/Database.h"
#include "src/model/Constants.h"
#include "src/model/Model.h"
#include "src/fit/AbsFunc.h"
#include "src/fit/FuncTerm0.h"
#include "src/fit/FuncB.h"
#include "src/fit/FuncSIdealN.h"
#include "src/fit/FuncSReal.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"AbsFunc", payloadCode, "@",
"FuncB", payloadCode, "@",
"FuncSIdealN", payloadCode, "@",
"FuncSReal", payloadCode, "@",
"FuncTerm0", payloadCode, "@",
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
