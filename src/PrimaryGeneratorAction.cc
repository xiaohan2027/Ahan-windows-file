

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4ParticleGun.hh"

#include "G4RandomDirection.hh"

#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),fParticleGun1(),fParticleGun2(),fParticleGun3()
{
  G4int n_particle = 1000;
  fParticleGun1= new G4ParticleGun(n_particle);
  fParticleGun2= new G4ParticleGun(n_particle);
  fParticleGun3= new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    //= particleTable->FindParticle(particleName="e-");
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun1->SetParticleDefinition(particle);
  fParticleGun1->SetParticleEnergy(0.662*MeV);
  fParticleGun1->SetParticlePosition(G4ThreeVector(0*cm,0*cm,-10*cm));
  //fParticleGun1->SetParticleTime(0.0*ns);

   fParticleGun2->SetParticleDefinition(particle);
   fParticleGun2->SetParticleEnergy(1.173*MeV);
   fParticleGun2->SetParticlePosition(G4ThreeVector(0*cm,0*cm,-15*cm));
  //fParticleGun2->SetParticleTime(0.0*ns);
  
  fParticleGun3->SetParticleDefinition(particle);
  fParticleGun3->SetParticleEnergy(1.333*MeV);
  fParticleGun3->SetParticlePosition(G4ThreeVector(2*cm,0*cm,-15*cm));
  //fParticleGun3->SetParticleTime(0.0*ns);
  	
   
  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun1;
  delete fParticleGun2;
  delete fParticleGun3;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ //G4ParticleGun* fParticleGun[3];
 // int sourceIndex = G4UniformRand() * 3;  // numSources 是粒子源的数量
    //G4ParticleGun* particleGun = fParticleGun[sourceIndex];
 G4double Position[3];

	G4double th = acos(1.0-2*G4UniformRand());
	G4double ph = G4UniformRand()*2.0*CLHEP::pi;
 
	Position[0] = sin(th)*cos(ph);
	Position[1] = sin(th)*sin(ph);
	Position[2] = cos(th);

    //G4ThreeVector positionPri = G4ThreeVector(Position[0],Position[1],Position[2]);//定义各项同性

	G4ThreeVector positionPri = G4ThreeVector(0,0,1);//定义锥轴的方向

	//fParticleGun->SetParticlePosition(G4ThreeVector(0*cm,0*cm,0*cm));//define particle position

	//get particle momentum direction
	G4double Direction[3];
	
	G4double HalfAngle=30*deg; //圆锥半角的度数；
    G4double theta = acos(1+(cos(HalfAngle)-1)*G4UniformRand());

    //G4double theta = acos(1.0-G4UniformRand());//圆锥半角为90度

  //G4double theta =  acos(1.0-2*G4UniformRand());//当固定某个发射方向时，半角设置为0～pai，则也可以实现各项同性
	G4double phi = G4UniformRand()*2.0*CLHEP::pi;
 
	Direction[0] = sin(theta)*cos(phi);
	Direction[1] = sin(theta)*sin(phi);
	Direction[2] = cos(theta);
 
 	G4ThreeVector directPri = G4ThreeVector(Direction[0],Direction[1],Direction[2]);
	directPri.rotateUz(positionPri);//朝着Z轴发射，但Z锥轴方向改为positionPri

	fParticleGun1->SetParticleMomentumDirection(directPri); 
  fParticleGun2->SetParticleMomentumDirection(directPri);
  fParticleGun3->SetParticleMomentumDirection(directPri);





  // G4double theta = G4UniformRand()* 180.0*deg;
  // G4double phi = G4UniformRand()*180.0*2.0*deg;  

  // G4double u = sin(theta)*cos(phi);
  // G4double v = sin(theta)*sin(phi);
  // G4double w = cos(theta);

  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(u,v,w));


//particleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun1->GeneratePrimaryVertex(anEvent);
  fParticleGun2->GeneratePrimaryVertex(anEvent);
  fParticleGun3->GeneratePrimaryVertex(anEvent);
}
 
 //create vertex
  //   

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

