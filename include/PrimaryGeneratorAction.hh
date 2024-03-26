
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "Gunfunction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
   ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    const G4ParticleGun* GetParticleGun() const { return fParticleGun1;return fParticleGun2;return fParticleGun3;}//return fParticleGun[3];

  private:
    //G4ParticleGun*  fParticleGun[3]; 
     G4ParticleGun* fParticleGun1;
     G4ParticleGun* fParticleGun2;
  G4ParticleGun* fParticleGun3;
   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


     //pointer a to G4 service class