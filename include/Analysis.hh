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
// $Id: Analysis.hh 76431 2013-11-10 20:28:49Z kmura $
//
/// @file Analysis.hh
/// @brief Define histograms

#ifndef ANALYSIS_MANAGER_H
#define ANALYSIS_MANAGER_H

#include "G4ThreeVector.hh"
#include <tools/histo/h1d>
#include <tools/histo/h2d>

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class G4Track;
class G4Step;
class G4ParticleDefinition;

class Analysis {
public:
  ~Analysis();

  static Analysis* GetAnalysis();

  void Book();
  void EndOfRun();

  void Update();
  void Clear();
  void Save(const G4String& fname);
  void Close();

  void FillDet(const G4ParticleDefinition* pd, G4double e);
  void ScoreNewTrack(const G4Track* track);

  void ClearIncidentFlag();

private:
  Analysis();
  DISALLOW_COPY_AND_ASSIGN(Analysis);

  //Histograms handlers
  G4int fDet_gamma;
  G4int fDet_gamma_low;
  G4int fDet_electron;
  G4int fDet_electron_low;

  static G4ThreadLocal G4int fincidentFlag;

};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void Analysis::ClearIncidentFlag()
{
  fincidentFlag = false;
}

#endif
