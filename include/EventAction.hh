
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
class RunAction;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction*);
   ~EventAction();

  public:
    virtual void   BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
     //void Add(double edepStep);
    //{G4double E1=0;
     // E1+=edepStep;}

  //void Add_Detector_Edep(G4double edep, G4int ii, G4int jj) { Detector_E[ii][jj] += edep;}  

    /*G4int GetMyEventId() {return MyEvent;}
    void AddEdep_track(G4double E, G4int num) { Energy_Array[num] += E;}

    void GetPositionX_track(G4double X, G4int num) {PositionX_track[num] = X;}
    void GetPositionY_track(G4double Y, G4int num) {PositionY_track[num] = Y;}
    void GetPositionZ_track(G4double Z, G4int num) {PositionZ_track[num] = Z;}

    void GetPositionX_Copy(G4double X, G4int num) {PositionX_Copy[num] = X;}
    void GetPositionY_Copy(G4double Y, G4int num) {PositionY_Copy[num] = Y;}
    void GetPositionZ_Copy(G4double Z, G4int num) {PositionZ_Copy[num] = Z;}

    void GetCopynum(G4int num) {Copynum = num;}
    void GetProcess(G4String name) {ProcessName = name;} */

  bool Flag;

  private:

    /*G4double  Energy_track;
    G4double  PositionX_track[300];
    G4double  PositionY_track[300]; 
    G4double  PositionZ_track[300];
    G4double  PositionX_Copy[300];
    G4double  PositionY_Copy[300]; 
    G4double  PositionZ_Copy[300];

    G4int     Copynum;
    G4double  Energy_Array[300];*/
    G4String  ProcessName;


  private:
    G4double  EnergyDeposit;   
    G4int MyEvent;   
     G4int MyEventId;
     //G4double E1;
    //G4double E2;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
