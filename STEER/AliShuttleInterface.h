#ifndef ALI_SHUTTLE_INTERFACE_H
#define ALI_SHUTTLE_INTERFACE_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//
// abstract interface class to AliShuttle
//

#include <TObject.h>
#include <TString.h>

class TList;
class AliCDBMetaData;
class AliPreprocessor;
class AliCDBPath;

class AliShuttleInterface : public TObject
{
  public:
    enum System { kDAQ = 0, kDCS, kHLT };
    enum { kNDetectors = 18 }; // number of subdetectors in ALICE

    virtual UInt_t Store(const AliCDBPath& path, TObject* object, AliCDBMetaData* metaData,
    				Int_t validityStart = 0, Bool_t validityInfinite = kFALSE) = 0;
    virtual UInt_t StoreReferenceData(const AliCDBPath& path, TObject* object, AliCDBMetaData* metaData) = 0;
    virtual const char* GetFile(Int_t system, const char* detector, const char* id, const char* source) = 0;
    virtual TList* GetFileSources(Int_t system, const char* detector, const char* id) = 0;
    virtual const char* GetRunParameter(const char* lbEntry) = 0;
    virtual void Log(const char* detector, const char* message) = 0;

    virtual void RegisterPreprocessor(AliPreprocessor* preprocessor) = 0;

    static const char* GetSystemName(UInt_t system) {return (system < 3) ? fkSystemNames[system] : 0;}

    static const char* GetOfflineDetName(const char* detName);
    static const char* GetDetName(UInt_t detPos);
    static Int_t GetDetPos(const char* detName);
    static UInt_t NDetectors() {return kNDetectors;}

    static TString GetMainCDB () {return fgkMainCDB;}
    static void SetMainCDB (TString mainCDB) {fgkMainCDB = mainCDB;}
    static TString GetLocalCDB () {return fgkLocalCDB;}
    static void SetLocalCDB (TString localCDB) {fgkLocalCDB = localCDB;}

    static TString GetMainRefStorage() {return fgkMainRefStorage;}
    static void SetMainRefStorage (TString mainRefStorage) {fgkMainRefStorage = mainRefStorage;}
    static TString GetLocalRefStorage() {return fgkLocalRefStorage;}
    static void SetLocalRefStorage (TString localRefStorage) {fgkLocalRefStorage = localRefStorage;}

    static void SetShuttleTempDir (const char* tmpDir);
    static const char* GetShuttleTempDir() {return fgkShuttleTempDir.Data();}
    static void SetShuttleLogDir (const char* logDir);
    static const char* GetShuttleLogDir() {return fgkShuttleLogDir.Data();}

  protected:
    static const char* fkSystemNames[3];  		// names of the systems providing data to the shuttle
    static const char* fgkDetName[kNDetectors]; 	// names of detectors' preprocessors (3-letter code convention)
    static const char* fgkOfflineDetName[kNDetectors];  // names of detectors in OCDB (AliRoot naming convention)

    static TString fgkMainCDB;		// URI of the main (Grid) CDB storage
    static TString fgkLocalCDB;		// URI of the local backup CDB storage
    static TString fgkMainRefStorage;	// URI of the main (Grid) REFERENCE storage
    static TString fgkLocalRefStorage;	// URI of the local REFERENCE storage

    static TString fgkShuttleTempDir;	// path of SHUTTLE temp folder
    static TString fgkShuttleLogDir;	// path of SHUTTLE log folder

  private:
    ClassDef(AliShuttleInterface, 0);
};

#endif
