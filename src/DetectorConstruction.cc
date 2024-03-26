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
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class



#include "DetectorConstruction.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Ellipsoid.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
using namespace CLHEP;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4double z, a, density;
  G4String name, symbol;
  G4int ncomponents, natoms;

 
  //********************************************************mCdZnTe
  G4bool isotopes = false;
  G4Element *Cd = nist->FindOrBuildElement("Cd", isotopes);
  G4Element *Te = nist->FindOrBuildElement("Te", isotopes);
  G4Element *Zn = nist->FindOrBuildElement("Zn", isotopes);

  G4Material *CdTe = new G4Material("CdTe", density = 5.8 * g / cm3, ncomponents = 2);//材料定义
  CdTe->AddElement(Cd, natoms = 1);
  CdTe->AddElement(Te, natoms = 1);   

  G4Material *ZnTe = new G4Material("ZnTe", density = 6.34 * g / cm3, ncomponents = 2);//材料定义
  ZnTe->AddElement(Zn, natoms = 1);
  ZnTe->AddElement(Te, natoms = 1);     

  G4Material *mCdZnTe = new G4Material("mCdZnTe", density = 5.854 * g / cm3, ncomponents = 2);//材料定义
  mCdZnTe->AddMaterial(CdTe,0.48);
  mCdZnTe->AddMaterial(ZnTe,0.02);


//**************************************************



  //     
  // World
  //
  G4double world_sizeXY = 2*m;
  G4double world_sizeZ  = 2*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
//
// ========= Detector ========= //
//

G4ThreeVector posdetpixel = G4ThreeVector(0, 0, 0*cm); //position scater


//material

  G4Material *scater_mat = new G4Material("scater_mat", density = 5.854 * g / cm3, ncomponents = 2);//材料定义
  scater_mat ->AddMaterial(CdTe,0.48);
  scater_mat ->AddMaterial(ZnTe,0.02);

// density = 2.33*g/cm3;
// a = 28.085*g/mole;
// G4Material* scater_mat = new G4Material(name="scater_mat", z=14, a, density);  //si 

//scater solid
G4double Scaterpixel_x = 2.5*mm;
G4double Scaterpixel_y = 2.5*mm;
G4double Scaterpixel_z = 3*mm;

G4int Scaterpixelnum = 11;

G4Box* solidScaterpixel = new G4Box("scater",0.5*Scaterpixel_x, 0.5*Scaterpixel_y, 0.5*Scaterpixel_z); //its size

//logical volume
G4LogicalVolume* logicScaterpixel =                         
    new G4LogicalVolume(solidScaterpixel,    //its solid
    scater_mat,                           //its material
    "scater");                     //its name

//scater physical
    for (int jx=0;jx<Scaterpixelnum;jx++)
    {
        for (int jy=0;jy<Scaterpixelnum;jy++)
            { 
                posdetpixel = G4ThreeVector(-(jx-0.5*(Scaterpixelnum-1))*Scaterpixel_x, -(jy-0.5*(Scaterpixelnum-1))*Scaterpixel_y, 0);  //position scater pixel
                new G4PVPlacement(0,                       //no rotation
                                  posdetpixel,                    //at position
                                  logicScaterpixel,             //its logical volume
                                  "scater",                //its name
                                  logicWorld,                //its mother  volume
                                  false,                   //no boolean operation
                                  (jy+ jx*Scaterpixelnum) ,                       //copy number
                                  checkOverlaps);          //overlaps checking 
          }
    }

//material

// G4Material *absorb_mat = new G4Material("absorb_mat", density = 5.854 * g / cm3, ncomponents = 2);//材料定义
// absorb_mat->AddMaterial(CdTe,0.48);
// absorb_mat->AddMaterial(ZnTe,0.02);

density = 5.323*g/cm3;
a = 72.5*g/mole;
G4Material* absorb_mat = new G4Material(name="absorb_mat", z=32, a, density);  //Ge

//absorb solid
G4double Absorbpixel_x = 2.5*mm;
G4double Absorbpixel_y = 2.5*mm;
 G4double Absorbpixel_z = 3*mm;
G4int Absorbpixelnum = 11;

G4Box* solidAbsorbpixel = new G4Box("absorb",0.5*Absorbpixel_x, 0.5*Absorbpixel_y, 0.5*Absorbpixel_z); //its size

//absorb logicalvolume
G4LogicalVolume* logicAbsorbpixel =                         
    new G4LogicalVolume(solidAbsorbpixel,    //its solid
    absorb_mat,                           //its material
    "absorb");                     //its name


G4double distence=3*mm;


//absorb physical
    for (int jx=0;jx<Absorbpixelnum;jx++)
    {
        for (int jy=0;jy<Absorbpixelnum;jy++)
            { 

                posdetpixel = G4ThreeVector(-(jx-0.5*(Absorbpixelnum-1))*Absorbpixel_x, -(jy-0.5*(Absorbpixelnum-1))*Absorbpixel_y, 
                0.5*Scaterpixel_z+distence+0.5*Absorbpixel_z );  // position absorb

                new G4PVPlacement(0,                       //no rotation
                                  posdetpixel,                    //at position
                                  logicAbsorbpixel,             //its logical volume
                                  "absorb",                //its name
                                  logicWorld,                //its mother  volume
                                  false,                   //no boolean operation
                                  (jy+ jx*Absorbpixelnum) + (Scaterpixelnum*Scaterpixelnum),                       //copy number
                                  checkOverlaps);          //overlaps checking 
          }
    } 


 //wastbin200L
 
 //material
density = 7.874*g/cm3;
a = 55.85*g/mole;
G4Material* Fe = new G4Material(name="Fe", z=26, a, density);

//solid
G4double pRMin=0.27*m;G4double pRMax=0.275*m;G4double pDz1=0.435*m;G4double pDz2=0.01*m;G4double pRMinn=0*m;
G4ThreeVector Bullet_Transition1(0,0,pDz1);G4ThreeVector Bullet_Transition2(0,0,-pDz1);//平移
G4RotationMatrix* rotatt=new G4RotationMatrix();
rotatt->rotateX(0 * deg);//旋转
G4Tubs* solidironside = new G4Tubs("wastbinside",pRMin,pRMax,pDz1,0,2*pi);
G4Cons* solidironbottom = new G4Cons("wastbinbottom",pRMinn,pRMin,pRMinn,pRMin,pDz2,0,2*pi);
G4Cons* solidirontop = new G4Cons("wastbintop",pRMinn,pRMin,pRMinn,pRMin,pDz2,0,2*pi);
G4UnionSolid* solidiron1 =new G4UnionSolid("wastbin1", solidironside,solidironbottom,rotatt,Bullet_Transition1);//第一次组合
G4UnionSolid* solidiron2 =new G4UnionSolid("wastbin2", solidiron1,solidirontop,rotatt,Bullet_Transition2);//第二次组合，选择合适的布尔函数，关键是布尔函数的参数
// logicalvolume
G4LogicalVolume* logiciron =                         
    new G4LogicalVolume(solidiron2,    //its solid
    Fe,                           //its material
    "wastbin2");                     //its name

// physical
G4ThreeVector pos = G4ThreeVector(0, 0*cm, -30*cm);
G4RotationMatrix* rotat=new G4RotationMatrix();
rotat->rotateX(90.0 * deg);

//G4RotationMatrix* rotationMatrix;
//rotationMatrix->rotateX(90.0 * deg);  //和上面的区别是什么？  直接对对象进行操作，相当于直接对int a的a进行操作，改变的是对象（变量）本身，
                                         //如果对指针操作，只是获取了该变量，而这个该变量并没有应用到对象上

new G4PVPlacement(rotat,                       //no rotation  这个旋转是作用在对象身上，如果用变量获取的话则无法应用到对象上，只有将RotationMatrix实例化才能作为一个参数用于物理体这个对象
                  pos,                    //at position
                  logiciron,             //its logical volume
                   "wastbin2",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                  0,                       //copy number
                   checkOverlaps);          //overlaps checking 

/*//medium沙子
//material
 //density = 2.65*g/cm3;
 G4Element *Si = nist->FindOrBuildElement("Si", isotopes);
  G4Element *O = nist->FindOrBuildElement("O", isotopes);
  G4Material *SiO2 = new G4Material("SiO2", density = 2.65*g/cm3, ncomponents = 2);//材料定义
 SiO2->AddElement(Si, natoms = 1);
  SiO2->AddElement(O, natoms = 2); 

//solid
G4double pRMins=0*m;G4double pRMaxs=0.26*m;G4double pDz1s=0.435*m;
G4Tubs* solidsio2 = new G4Tubs("shazi",pRMins,pRMaxs,pDz1s,0,2*pi);

// logicalvolume
G4LogicalVolume* logicsio2 =                         
    new G4LogicalVolume(solidsio2,    //its solid
    SiO2,                           //its material
    "shazi");                     //its name
  
// physical
G4ThreeVector poss = G4ThreeVector(0, 0*cm, -30*cm);
G4RotationMatrix* rotats=new G4RotationMatrix();
rotats->rotateX(90.0 * deg);

//G4RotationMatrix* rotationMatrix;
//rotationMatrix->rotateX(90.0 * deg);  //和上面的区别是什么？  直接对对象进行操作，相当于直接对int a的a进行操作，改变的是对象（变量）本身，
                                         //如果对指针操作，只是获取了该变量，而这个该变量并没有应用到对象上

new G4PVPlacement(rotat,                       //no rotation  这个旋转是作用在对象身上，如果用变量获取的话则无法应用到对象上，只有将RotationMatrix实例化才能作为一个参数用于物理体这个对象
                  poss,                    //at position
                  logicsio2,             //its logical volume
                   "shazi",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                  0,                       //copy number
                   checkOverlaps);          //overlaps checking */


//medium水
//material
 //density = 1.00*g/cm3;
 G4Element *H = nist->FindOrBuildElement("H", isotopes);
  G4Element *O = nist->FindOrBuildElement("O", isotopes);
  G4Material *H2O = new G4Material("H2O", density = 1.00*g/cm3, ncomponents = 2);//材料定义
 H2O->AddElement(O, natoms = 1);
  H2O->AddElement(H, natoms = 2); 

//solid
G4double pRMins=0*m;G4double pRMaxs=0.26*m;G4double pDz1s=0.435*m;
G4Tubs* solidh2o = new G4Tubs("water",pRMins,pRMaxs,pDz1s,0,2*pi);

// logicalvolume
G4LogicalVolume* logich2o =                         
    new G4LogicalVolume(solidh2o,    //its solid
    H2O,                           //its material
    "water");                     //its name
  
// physical
G4ThreeVector poss = G4ThreeVector(0, 0*cm, -30*cm);
G4RotationMatrix* rotats=new G4RotationMatrix();
rotats->rotateX(90.0 * deg);

//G4RotationMatrix* rotationMatrix;
//rotationMatrix->rotateX(90.0 * deg);  //和上面的区别是什么？  直接对对象进行操作，相当于直接对int a的a进行操作，改变的是对象（变量）本身，
                                         //如果对指针操作，只是获取了该变量，而这个该变量并没有应用到对象上

new G4PVPlacement(rotat,                       //no rotation  这个旋转是作用在对象身上，如果用变量获取的话则无法应用到对象上，只有将RotationMatrix实例化才能作为一个参数用于物理体这个对象
                  poss,                    //at position
                  logich2o,             //its logical volume
                   "water",                //its name
                   logicWorld,                //its mother  volume
                   false,                   //no boolean operation
                  0,                       //copy number
                   checkOverlaps);          //overlaps checking 
//*****************************************************************初始标准的

// for (int jz=0;jz<2;jz++)
// {

//     for (int jx=0;jx<detpixelnum;jx++)
//     {
//         for (int jy=0;jy<detpixelnum;jy++)
//             { 

//                 posdetpixel = G4ThreeVector(-(jx-0.5*(detpixelnum-1))*detpixel_x, -(jy-0.5*(detpixelnum-1))*detpixel_y, 0.2*cm * jz);
//                 new G4PVPlacement(0,                       //no rotation
//                                   posdetpixel,                    //at position
//                                   logicdetpixel,             //its logical volume
//                                   "Det_phys",                //its name
//                                   logicWorld,                //its mother  volume
//                                   false,                   //no boolean operation
//                                   (jy+ jx*detpixelnum) + (detpixelnum*detpixelnum)*jz,                       //copy number
//                                   checkOverlaps);          //overlaps checking 
//           }
//     }
// }

//***************************************************

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  //
  // ----- vis -----
  //

  G4VisAttributes* transgrey=new G4VisAttributes(G4Colour(0.64,0.7,0.7,0.5));
  transgrey->SetForceSolid(true);

  G4VisAttributes* transblue=new G4VisAttributes(G4Colour(0.01,0.98,0.9,0.3));
  transblue->SetForceSolid(true);

  G4VisAttributes* transyellow=new G4VisAttributes(G4Colour(0.8,0.9,0.1,0.9));
  transyellow->SetForceSolid(true);

  G4VisAttributes* transgreen=new G4VisAttributes(G4Colour(0.2,0.98,0.1,0.9));
  transgreen->SetForceSolid(true);

  G4VisAttributes* transred=new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  transred->SetForceSolid(true);

  logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

  logicScaterpixel->SetVisAttributes(transblue); // logical的颜色
  logicAbsorbpixel->SetVisAttributes(transyellow); // logical的颜色
  //logicsio2->SetVisAttributes(transyellow);
  logiciron->SetVisAttributes(transblue);
   logich2o->SetVisAttributes(transyellow);

  //Fe_log->SetVisAttributes(transblue);
  //Det_log->SetVisAttributes(transyellow);

  //
  //always return the physical World
  //
 
  return physWorld;

}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
