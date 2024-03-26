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
// $Id: B5Analysis.hh 66536 2012-12-19 14:32:36Z ihrivnac $
//
/// \file B5Analysis.hh
/// \brief Selection of the analysis technology

#ifndef Gunfunction_h
#define Gunfunction_h 1
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include <CLHEP/Units/PhysicalConstants.h>
#include "G4ThreeVector.hh"
inline G4ThreeVector SpherePosition(G4double r1,G4double r2,G4ThreeVector location){
G4double rminv=r1/mm;
G4double rmaxv=r2/mm;
G4double rin=pow(G4UniformRand()*(pow(rmaxv,3)-pow(rminv,3)+pow(rminv,3)),1./3);
//G4double theta=acos(2*G4UniformRand()-1);
G4double costheta=2*G4UniformRand()-1;
G4double sintheta2=1-costheta*costheta;
if(sintheta2<0.) sintheta2=0.;
G4double sintheta=std::sqrt(sintheta2);
G4double phi=CLHEP::twopi*G4UniformRand();
G4double px=rin*sintheta*std::cos(phi)*mm+location.x();
G4double py=rin*sintheta*std::sin(phi)*mm+location.y();
G4double pz=rin*costheta*mm+location.z();
return G4ThreeVector(px,py,pz);
}
inline G4ThreeVector BoxPosition(G4double lenx,G4double leny,G4double lenz,G4ThreeVector location){
G4double px=(G4UniformRand()-0.5)*lenx+location.x();
G4double py=(G4UniformRand()-0.5)*leny+location.y();
G4double pz=(G4UniformRand()-0.5)*lenz+location.z();
return G4ThreeVector(px,py,pz);
}



//#include "g4xml.hh"
//#include "g4csv.hh"

#endif
