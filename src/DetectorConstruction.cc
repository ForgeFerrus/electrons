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
// $Id: DetectorConstruction.cc 76431 2013-11-10 20:28:49Z kmura $
//
/// @file DetectorConstruction.hh
/// @brief Define geometry

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "DetectorConstruction.hh"
#include "DetSD.hh"

typedef G4LogicalVolume G4LV;
typedef G4PVPlacement G4PVP;
typedef G4VisAttributes G4VA;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::DetectorConstruction()
  : flv_Det(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4VisAttributes* va;
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // world volume
  const G4double DXYZ_WORLD = 20*cm;
  G4Box* sld_world = new G4Box("world",
                               DXYZ_WORLD/2., DXYZ_WORLD/2., DXYZ_WORLD/2);

  G4Material* W = nist-> FindOrBuildMaterial("G4_W");
  G4Material* air = nist-> FindOrBuildMaterial("G4_AIR");
  G4LV* lv_world = new G4LogicalVolume(sld_world, air, "world");
  G4PVP* world = new G4PVPlacement(0, G4ThreeVector(), "AREA",
                                   lv_world, 0, false, 0);
  // vis. attributes
  va = new G4VA(G4Color(1.,1.,1.));
  va-> SetVisibility(false);
  lv_world-> SetVisAttributes(va);
  //     
  //  Detector volume
  G4Tubs* solidCheck =    
    new G4Tubs("Check",                    //its name
        0*cm, 1*cm, 0.05*cm,0.*deg,360*deg); //its size
  
   flv_Det = new G4LV(solidCheck,            //its solid
                        air,             //its material
                        "Check");         //its name
   new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0*cm, 0*cm, 2*cm),      //at (0,0,0)
                    flv_Det,                //its logical volume
                    "Check",              //its name
                    lv_world,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  // Target
  G4Tubs* solidH3Ti =    
    new G4Tubs("H3Ti",                    //its name
        0*cm, 5*cm, 0.1025*cm,0.*deg,360*deg); //its size
  
  G4LogicalVolume* logicH3Ti =                         
    new G4LogicalVolume(solidH3Ti,         //its solid
                        W,             //its material
                        "H3Ti");         //its name
   new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0*cm,0*cm,0*cm),      //at (0,0,0)
                    logicH3Ti,                //its logical volume
                    "H3Ti",              //its name
                    lv_world,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  return world;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::ConstructSDandField()
{
  flv_Det-> SetSensitiveDetector(new DetSD("Detector"));
}
