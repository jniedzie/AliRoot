/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/


/* $Id$ */

//---
//  Produces the data needed to calculate the quality assurance. 
//  All data must be mergeable objects.
//  A. Mastroserio
//---

// --- ROOT system ---
#include <TClonesArray.h>
#include <TFile.h> 
#include <TH1F.h> 
#include <TH2F.h>
#include <TH1I.h> 
#include <TDirectory.h>
#include <Riostream.h>
// --- Standard library ---

// --- AliRoot header files ---
#include "AliESDCaloCluster.h"
#include "AliESDEvent.h"
#include "AliLog.h"
#include "AliT0digit.h"
#include "AliT0hit.h"
#include "AliT0RecPoint.h"
#include "AliT0QADataMaker.h"
#include "AliQAChecker.h"

ClassImp(AliT0QADataMaker)
           
//____________________________________________________________________________ 
  AliT0QADataMaker::AliT0QADataMaker() : 
  AliQADataMaker(AliQA::GetDetName(AliQA::kT0), "T0 Quality Assurance Data Maker")
  //  fhHitsTime(0x0),
  // fhHitsAmp(0x0),
  // fhHitsEff(0x0),
  //  fhDigCFD(0x0),
  //  fhDigLEDamp(0x0),
  //  fhDigQTC(0x0),
  // fhDigMean(0x0),
  //  fhDigEff(0x0),
  //  fhRecCFD(0x0),
  //  fhRecLEDamp(0x0),
  //  fhRecQTC(0x0),
  //  fhRecMean(0x0),
  //  fhRecEff(0x0),
  //  fhESDMean(0x0),
  //  fhESDVertex(0x0)

{
  // ctor
  /*
  for(Int_t i=0; i<24; i++) {
    fhHitsTime[i]=0x0;
   fhDigCFD[i]=0x0;
    fhDigLEDamp[i]=0x0;
    fhRecCFD[i]=0x0;
    fhRecLEDamp[i]=0x0;
    fhRecQTC[i]=0x0;
  }
  */
 //   fDetectorDir = fOutput->GetDirectory(GetName()) ;  
//   if (!fDetectorDir) 
//     fDetectorDir = fOutput->mkdir(GetName()) ;  
}

//____________________________________________________________________________ 
AliT0QADataMaker::AliT0QADataMaker(const AliT0QADataMaker& qadm) :
  AliQADataMaker() 
 //  fhHitsTime(0x0),
 // fhHitsEff(0x0),
  //  fhDigCFD(0x0),
  //  fhDigLEDamp(0x0),
  //  fhDigQTC(0x0),
  // fhDigMean(0x0),
  // fhDigEff(0x0),
  //  fhRecCFD(0x0),
  //  fhRecLEDamp(0x0),
  //  fhRecQTC(0x0),
  // fhRecMean(0x0),
  // fhRecEff(0x0),
  // //  fhESDMean(0x0),
  // fhESDVertex(0x0)
{
  //copy ctor 
  /*
  for(Int_t i=0; i<24; i++) {
    fhHitsTime[i]=0x0;
    fhDigCFD[i]=0x0;
    fhDigLEDamp[i]=0x0;
    fhRecCFD[i]=0x0;
    fhRecLEDamp[i]=0x0;
    fhRecQTC[i]=0x0;
  }
  */
  SetName((const char*)qadm.GetName()) ; 
  SetTitle((const char*)qadm.GetTitle()); 
}

//__________________________________________________________________
AliT0QADataMaker& AliT0QADataMaker::operator = (const AliT0QADataMaker& qadm )
{
  // Equal operator.
  this->~AliT0QADataMaker();
  new(this) AliT0QADataMaker(qadm);
  return *this;
}
//____________________________________________________________________________
void AliT0QADataMaker::EndOfDetectorCycle(AliQA::TASKINDEX task, TList * list)
{
  //Detector specific actions at end of cycle
  // do the QA checking
  AliQAChecker::Instance()->Run(AliQA::kT0, task, list) ;
}

//____________________________________________________________________________
void AliT0QADataMaker::StartOfDetectorCycle()
{
  //Detector specific actions at start of cycle

}
 
//____________________________________________________________________________ 
void AliT0QADataMaker::InitHits()
{
  // create Hits histograms in Hits subdir
  TString timename;
  timename ="hHitTime";
  TH1F *    fhHitsTime[24];
  for (Int_t i=0; i<24; i++)
    {
      timename += i;
      if(i<12)  fhHitsTime[i] = new TH1F(timename.Data(),timename.Data(),100,2,3);
      else  
	fhHitsTime[i] = new TH1F(timename.Data(),timename.Data(),100,12,13);
      Add2HitsList( fhHitsTime[i],i);
    }
  /*
  TH2F *fhHitsEffA = new TH2F("hHitsEffA", "Hits Efficiency A side", 25,-0.5,24.5, 100,12,13 );
  Add2HitsList(fhHitsEffA,0);
  TH2F *fhHitsEffC = new TH2F("hHitsEffC", "Hits Efficiency C side", 25,-0.5,24.5, 100,2,3 );
  Add2HitsList(fhHitsEffC,1);
  */
}

//____________________________________________________________________________ 
void AliT0QADataMaker::InitDigits()
{
  // create Digits histograms in Digits subdir

  /*
  TH2F * fhDigCFD = new TH2F("fhDigCFD", " CFD digits",25,-0.5,24.5,100,100,1000);
  Add2DigitsList( fhDigCFD,0);
  TH2F *fhDigLEDamp = new TH2F("fhDigLEDamp", " LED-CFD digits",25,-0.5,24.5,100,100,1000);
  Add2DigitsList( fhDigLEDamp,1);
  TH2F * fhDigQTC = new TH2F("fhDigQTC", " QTC digits",25,-0.5,24.5,100,100,1000);
  Add2DigitsList( fhDigQTC,2);
  TH1F * fhDigMean = new TH1F("hDigMean","online mean signal", 100,500,600);
  Add2DigitsList( fhDigMean,23);
  */
  
  TString timename, ampname, qtcname;
  timename ="hDigCFD";
  ampname = "hDigLED";
  qtcname = "hDigQTC";

  TH1F *fhDigCFD[24]; TH1F * fhDigLEDamp[24]; TH1F *fhDigQTC[24];

  for (Int_t i=0; i<24; i++)
    {
      timename += i;
      ampname += i;
      qtcname += i;
      fhDigCFD[i] = new TH1F(timename.Data(), timename.Data(),100,100,1000);
      Add2DigitsList( fhDigCFD[i],i);
      fhDigLEDamp[i] = new TH1F(ampname.Data(), ampname.Data(),100,100,1000);
      Add2DigitsList( fhDigLEDamp[i],i+24);
      fhDigQTC[i] = new TH1F(qtcname.Data(), qtcname.Data(),100,100,1000);
      Add2DigitsList( fhDigQTC[i],i+48);
     }
  
  TH1F* fhDigEff = new TH1F("hDigEff","digits efficiency", 25,-0.5,24.5);
  Add2DigitsList( fhDigEff,72);
  TH1F* fhDigMean = new TH1F("hDigMean","online mean signal", 100,500,600);
  Add2DigitsList( fhDigMean,73);
  
}

//____________________________________________________________________________ 

void AliT0QADataMaker::InitRecPoints()
{
  // create cluster histograms in RecPoint subdir
  /* 
 TH2F * fhRecCFD = new TH2F("fhRecCFD", " CFD reconstructed",25,-0.5,24.5,100,12,13);
  Add2DigitsList( fhRecCFD,0);
  TH2F *fhRecLEDamp = new TH2F("fhRecLEDamp", " amplitude LED reconstructed",25,-0.5,24.5,100,1000,1000);
  Add2DigitsList( fhRecLEDamp,1);
 TH2F * fhRecQTC = new TH2F("fhRecQTC", " amplitude QTC reconstructed",25,-0.5,24.5,100,1000,1000);
  Add2DigitsList( fhRecQTC,2);
 TH1F * fhRecMean = new TH1F("hRecMean"," reconstructed mean signal",100,500,600);
  Add2DigitsList( fhRecMean,3);
  */ 
  
  TString timename,ampname, qtcname;
  timename ="hRecCFD";
  ampname = "hRecLED";
  qtcname = "hRecQTC";
  TH1F *fhRecCFD[24]; TH1F *fhRecLEDAmp[24];  TH1F * fhRecQTC[24];
  for (Int_t i=0; i<24; i++)
    {
      timename += i;
      ampname += i;
      qtcname += i;
      fhRecCFD[i] = new TH1F(timename.Data(), timename.Data(),100,100,1000);
     Add2RecPointsList ( fhRecCFD[i],i);
      fhRecLEDAmp[i] = new TH1F(ampname.Data(), ampname.Data(),100,100,1000);
    Add2RecPointsList ( fhRecLEDAmp[i],i+24);
      fhRecQTC[i] = new TH1F(qtcname.Data(), qtcname.Data(),100,100,1000);
    Add2RecPointsList ( fhRecQTC[i],i+48);
     }
   
  TH1F *fhRecEff = new TH1F("hRecEff","Efficiency rec.points",25,-0.5,24.5);
 Add2RecPointsList ( fhRecEff,72);
  TH1F * fhRecMean = new TH1F("hRecMean"," reconstructed mean signal",100,500,600);
 Add2RecPointsList( fhRecMean,73);
  
}
//____________________________________________________________________________
void AliT0QADataMaker::InitESDs()
{
  //create ESDs histograms in ESDs subdir
  TH1F *fhESDMean = new TH1F("hESDmean"," ESD mean",100,500,600);
  Add2ESDsList(fhESDMean, 0) ;
 TH1F * fhESDVertex = new TH1F("hESDvertex","EAD vertex",100,-50,50);
  Add2ESDsList(fhESDVertex, 1) ;


}
//____________________________________________________________________________
void AliT0QADataMaker::MakeHits(TObject * data)
{
  //fills QA histos for Hits
  TClonesArray * hits = dynamic_cast<TClonesArray *>(data) ; 
  if (!hits){
    AliError("Wrong type of hits container") ; 
  } else {
    TIter next(hits); 
    AliT0hit * hit ; 
    while ( (hit = dynamic_cast<AliT0hit *>(next())) ) {
      Int_t pmt=hit->Pmt();
      GetHitsData(pmt)->Fill(pmt,hit->Time()) ;
    }
  } 
}

//____________________________________________________________________________
void AliT0QADataMaker::MakeDigits( TObject * data)
{
  //fills QA histos for Digits
 
  TArrayI *digCFD = new TArrayI(24);
  TArrayI *digLED = new TArrayI(24);
  TArrayI *digQT0 = new TArrayI(24);
  TArrayI *digQT1 = new TArrayI(24);
  Int_t refpoint=0;

  TClonesArray * digits = dynamic_cast<TClonesArray *>(data) ; 
  
  if ( !digits) {
    AliError("Wrong type of digits container") ; 
  } else {
    TIter next(digits) ; 
    AliT0digit * digit ; 
    while ( (digit = dynamic_cast<AliT0digit *>(next())) ) {
      digit->GetTimeCFD(*digCFD);
      digit->GetTimeLED(*digLED);
      digit->GetQT0(*digQT0);
      digit->GetQT1(*digQT1);
      refpoint =  digit->RefPoint();
      for (Int_t i=0; i<24; i++)
	{
	  if (digCFD->At(i)>0) {
	    Int_t cfd=digCFD->At(i)- refpoint;
	    GetDigitsData(i) ->Fill(i,cfd);
	    GetDigitsData(i+24) -> Fill(i, digLED->At(i) - digCFD->At(i));
	    GetDigitsData(i+48) -> Fill(i, digQT1->At(i) - digQT0->At(i));
	    //	    fhDigEff->Fill(i);
	  }
	}  
    }
  }
  delete digCFD;
  delete digLED;
  delete digQT0;
  delete digQT1;

}


//____________________________________________________________________________
void AliT0QADataMaker::MakeRecPoints(TTree * clustersTree)
{
  //fills QA histos for clusters

   AliT0RecPoint* frecpoints= new AliT0RecPoint ();
    if (!frecpoints) {
    AliError("Reconstruct Fill ESD >> no recpoints found");
    return;
  }
  TBranch *brRec =clustersTree ->GetBranch("T0");
  if (brRec) {
    brRec->SetAddress(&frecpoints);
  }else{
    cerr<<"EXEC Branch T0 rec not found"<<endl;
    // exit(111);
    return;
  } 
    
  brRec->GetEntry(0);
  
  for ( Int_t i=0; i<24; i++) {
    GetRecPointsData(i) -> Fill(frecpoints -> GetTime(i)); 
    GetRecPointsData(i+24) -> Fill(frecpoints -> GetAmp(i));
    GetRecPointsData(i+48) -> Fill(frecpoints->AmpLED(i));
    //  if(frecpoints -> GetTime(i) > 0) fhRecEff->Fill(i);
  }
     GetRecPointsData(72) ->Fill(frecpoints->GetMeanTime());
  
}

//____________________________________________________________________________
void AliT0QADataMaker::MakeESDs(AliESDEvent * esd)
{
  //fills QA histos for ESD

  GetESDsData(0) -> Fill(esd->GetT0());
  GetESDsData(1)-> Fill(esd->GetT0zVertex());

}

