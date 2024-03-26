
#include "RunAction.hh"
#include "EventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip>
#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction*)
:G4UserEventAction()
{ } 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
    //delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{  //E1=0;
   
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//void EventAction::Add(double edepStep) 
 // { E1+=edepStep;}

void EventAction::EndOfEventAction(const G4Event*aEvent)
{
    // get analysis manager
  //G4int eventID= aEvent->GetEventID();
    //MyEvent = eventID;
    //for(G4int j=0; j<300; j++)
   // {
        //if(Energy_Array[j]>0)
       // {
          // fstream datafiletrack;
            //datafiletrack.open("Results.txt",ios::out|ios::app);//
           // datafiletrack<< MyEvent <<"\t"<<E1<<endl;
            //  j << "\t" << 
           // PositionX_track[j] << "\t" << PositionY_track[j] << "\t" << PositionZ_track[j] << "\t" << 
           // PositionX_Copy[j] << "\t" << PositionY_Copy[j] << "\t" << PositionZ_Copy[j] << "\t" << 
           // Energy_Array[j]  <<endl;
            //datafiletrack.close();
        //}
   // }
   // if (eventID%10000==0) G4cout<<" Event => "<< eventID<<endl;	

}

