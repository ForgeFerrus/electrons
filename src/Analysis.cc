//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

// $Id: Analysis.cc 76431 2013-11-10 20:28:49Z kmura $
//
/// @file Analysis.cc
/// @brief Define histograms

//#include "TFile.h"
//#include "TH1.h"
//#include "TH2.h"
//#include "TROOT.h"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include <G4AnalysisManager.hh>
#include "G4AutoDelete.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"

#ifdef TROOT
#include "g4root.hh"
#include "g4csv.hh"
#include "g4xml.hh"
#endif

G4ThreadLocal G4int Analysis::fincidentFlag = false;
G4ThreadLocal Analysis* the_analysis = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Analysis*
Analysis::GetAnalysis()
{
  if (!the_analysis)
    {
      the_analysis = new Analysis();
      G4AutoDelete::Register(the_analysis);
    }
  return the_analysis;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Analysis::Analysis() :
  fDet_gamma(0), fDet_gamma_low(0), fDet_electron(0), fDet_electron_low(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::Book()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  fDet_gamma = mgr->CreateH1("fDet_gamma", "Gamma rays in the Det", 5000, 0.001, 5, "MeV");
  fDet_gamma_low = mgr->CreateH1("fDet_gamma_low", "Gamma rays in the Det_low", 500, 0.001, 0.1, "MeV");
  fDet_electron = mgr->CreateH1("fDet_electron", "Electrons in the Det", 5000, 0.001, 5, "MeV");
  fDet_electron_low = mgr->CreateH1("fDet_electron_low", "Electrons in the Det-low", 500, 0.001, 0.1, "MeV");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Analysis::~Analysis()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::Update()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::Clear()
{
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::Save(const G4String& fname)
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->OpenFile(fname.c_str());
  mgr->Write();
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::Close()
{
  G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  mgr->CloseFile();
  return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
Analysis::FillDet(const G4ParticleDefinition* pd, G4double e)
{
      G4AnalysisManager* mgr = G4AnalysisManager::Instance();
  if ( pd == G4Gamma::Gamma()) {
      mgr->FillH1(fDet_gamma, e);
      mgr->FillH1(fDet_gamma_low, e);
    }
  else if ( pd == G4Electron::Electron()) {
      mgr->FillH1(fDet_electron, e);
      mgr->FillH1(fDet_electron_low, e);
    }
  }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

