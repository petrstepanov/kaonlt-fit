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
#include "src/util/FileUtils.h"
#include "src/util/TreeUtils.h"
#include "src/util/HistUtils.h"
#include "src/model/Database.h"
#include "src/model/Constants.h"
#include "src/model/Model.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Database(void *p = 0);
   static void *newArray_Database(Long_t size, void *p);
   static void delete_Database(void *p);
   static void deleteArray_Database(void *p);
   static void destruct_Database(void *p);
   static void streamer_Database(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Database*)
   {
      ::Database *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Database >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Database", ::Database::Class_Version(), "src/model/Database.h", 7,
                  typeid(::Database), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Database::Dictionary, isa_proxy, 16,
                  sizeof(::Database) );
      instance.SetNew(&new_Database);
      instance.SetNewArray(&newArray_Database);
      instance.SetDelete(&delete_Database);
      instance.SetDeleteArray(&deleteArray_Database);
      instance.SetDestructor(&destruct_Database);
      instance.SetStreamerFunc(&streamer_Database);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Database*)
   {
      return GenerateInitInstanceLocal((::Database*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Database*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_Model(void *p);
   static void deleteArray_Model(void *p);
   static void destruct_Model(void *p);
   static void streamer_Model(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Model*)
   {
      ::Model *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Model >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Model", ::Model::Class_Version(), "src/model/Model.h", 9,
                  typeid(::Model), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Model::Dictionary, isa_proxy, 16,
                  sizeof(::Model) );
      instance.SetDelete(&delete_Model);
      instance.SetDeleteArray(&deleteArray_Model);
      instance.SetDestructor(&destruct_Model);
      instance.SetStreamerFunc(&streamer_Model);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Model*)
   {
      return GenerateInitInstanceLocal((::Model*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Model*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Database::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Database::Class_Name()
{
   return "Database";
}

//______________________________________________________________________________
const char *Database::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Database*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Database::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Database*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Database::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Database*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Database::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Database*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Model::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Model::Class_Name()
{
   return "Model";
}

//______________________________________________________________________________
const char *Model::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Model*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Model::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Model*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Model::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Model*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Model::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Model*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Database::Streamer(TBuffer &R__b)
{
   // Stream an object of class Database.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> myNumber;
      R__b.CheckByteCount(R__s, R__c, Database::IsA());
   } else {
      R__c = R__b.WriteVersion(Database::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << myNumber;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Database(void *p) {
      return  p ? new(p) ::Database : new ::Database;
   }
   static void *newArray_Database(Long_t nElements, void *p) {
      return p ? new(p) ::Database[nElements] : new ::Database[nElements];
   }
   // Wrapper around operator delete
   static void delete_Database(void *p) {
      delete ((::Database*)p);
   }
   static void deleteArray_Database(void *p) {
      delete [] ((::Database*)p);
   }
   static void destruct_Database(void *p) {
      typedef ::Database current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Database(TBuffer &buf, void *obj) {
      ((::Database*)obj)->::Database::Streamer(buf);
   }
} // end of namespace ROOT for class ::Database

//______________________________________________________________________________
void Model::Streamer(TBuffer &R__b)
{
   // Stream an object of class Model.

   TQObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Model(void *p) {
      delete ((::Model*)p);
   }
   static void deleteArray_Model(void *p) {
      delete [] ((::Model*)p);
   }
   static void destruct_Model(void *p) {
      typedef ::Model current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Model(TBuffer &buf, void *obj) {
      ((::Model*)obj)->::Model::Streamer(buf);
   }
} // end of namespace ROOT for class ::Model

namespace {
  void TriggerDictionaryInitialization_kaonltmIfitmIdictionary_Impl() {
    static const char* headers[] = {
"src/util/FileUtils.h",
"src/util/TreeUtils.h",
"src/util/HistUtils.h",
"src/model/Database.h",
"src/model/Constants.h",
"src/model/Model.h",
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
class __attribute__((annotate("$clingAutoload$src/model/Database.h")))  Database;
class __attribute__((annotate("$clingAutoload$src/model/Model.h")))  Model;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "kaonltmIfitmIdictionary dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/util/FileUtils.h"
#include "src/util/TreeUtils.h"
#include "src/util/HistUtils.h"
#include "src/model/Database.h"
#include "src/model/Constants.h"
#include "src/model/Model.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Database", payloadCode, "@",
"Model", payloadCode, "@",
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
