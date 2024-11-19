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
// $Id: VoxelSD.cc 76431 2013-11-10 20:28:49Z kmura $
//
/// @file VoxelSD.cc
/// @brief Define detector sensitivity on voxels

//#include "G4MPImanager.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "Randomize.hh"
#include "Analysis.hh"
#include "DetSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetSD::DetSD(const G4String& name)
  : G4VSensitiveDetector(name)
{
  G4SDManager::GetSDMpointer()-> AddNewDetector(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetSD::~DetSD()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool DetSD::ProcessHits(G4Step* astep, G4TouchableHistory*)
{
  Analysis* myana = Analysis::GetAnalysis();

      G4ParticleDefinition* pd = astep->GetTrack()->GetDefinition();
      G4String name = pd->GetParticleName();
      G4double e = astep->GetTrack()->GetKineticEnergy();
//      G4double e = std::log10(astep->GetTrack()->GetKineticEnergy());
  myana-> FillDet(pd, e);
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetSD::Initialize(G4HCofThisEvent*)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetSD::EndOfEvent(G4HCofThisEvent*)
{
}
