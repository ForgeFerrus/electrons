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
//
// $Id: RunActionMaster.cc 82310 2014-06-14 00:27:39Z adotti $
//
/// @file RunActionMaster.cc
/// @brief Describe run actions
//#include "g4root.hh" //ROOT Format for output
//#include "g4xml.hh" //XML Format for output
//#include "g4csv.hh"

#include <stdio.h>
#include "G4Threading.hh"
#include "Analysis.hh"
#include "RunAction.hh"
#include "Run.hh"

RunAction::RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Run* RunAction::GenerateRun()
{
  return new Run;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RunAction::~RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void
RunAction::BeginOfRunAction(const G4Run*)
{
  Analysis* myana = Analysis::GetAnalysis();
  myana-> Clear();
  myana->Book();
}

void
RunAction::EndOfRunAction(const G4Run* arun)
{
  //This is executed by master thread. Workers have already
  //merged their histograms into this master threads
      G4String fname("dose-rank000");
      Analysis* myana = Analysis::GetAnalysis();
      myana-> Save(fname);
      myana-> Close();
}
