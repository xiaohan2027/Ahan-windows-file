
#include "RunAction.hh"
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

RunAction::RunAction()
  : G4UserRunAction()
{
  G4RunManager::GetRunManager()->SetPrintProgress(1);
    

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  //delete G4AnalysisManager::Instance(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*aRun)
{ G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
fstream dataFile;
    G4String filename = "Results.txt";
      
    dataFile.open(filename,ios::out|ios::trunc);
    dataFile<<"E1"<<endl;
  // dataFile<<"eventID"<<"\t"<<"TrackID"<<"\t" <<"Xpos"<<"\t"<<"Ypos"<< "\t"<<"Zpos" <<"\t"<<"edepStep"<< "\t"<<"kine"
  // << "\t"<<"Seckine"<<"\t"<<"name"<<"\t"<<"processN"<<endl;
    dataFile.close();
  
  /*G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
    
    fstream dataFile;
    G4String filename = "Results.txt";
      
    dataFile.open(filename,ios::out|ios::trunc);
    dataFile<<"Event"<<"\t"<<"Number"<<"\t" 
    <<"Position_X"<<"\t"<<"Position_Y"<< "\t"<<"Position_Z" 
    <<"Copypos_X"<<"\t"<<"Copypos_Y"<< "\t"<<"Copypos_Z" 
    <<"\t"<<"DepEnergy"<<endl;
    dataFile.close();*/
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*aRun)
{
  G4cout << "Number of event = " << aRun->GetNumberOfEvent() << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
