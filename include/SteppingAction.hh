
#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class RunAction;
class TrackingAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction*,RunAction*, TrackingAction*);
   ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
    
  private: 
    EventAction* fEventAction;  
    RunAction* fRunAction;
    TrackingAction* fTrackaction;
    G4double particleE = 0;  
    G4double fseckine;
    G4double E1=0;
    G4double E2;
    G4int TrackIDold = 0;
//G4double  Energy_Array[300];
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
