
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <typeinfo>
using namespace std;  
#include "G4Alpha.hh"
#include "G4Track.hh"
#include "TrackingAction.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <typeinfo>
using namespace std;  
#include <fstream> 
#include "G4Step.hh"                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* event,RunAction* run,TrackingAction* trac)
: G4UserSteppingAction(),fEventAction(event),fRunAction(run),fTrackaction(trac)
{  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{ G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4Track* theTrack = aStep->GetTrack();                                         //获取径迹
  G4String particlename=aStep->GetTrack()->GetDefinition()->GetParticleName() ;    //获得粒子名称
	const G4StepPoint* fpPreStepPoint = aStep ->GetPreStepPoint();   //步的前点
	const G4StepPoint* fpPostStepPoint = aStep ->GetPostStepPoint(); //步的后点
  //G4int eventID = fEventAction->GetMyEventId();
  G4int TrackID = theTrack->GetTrackID();
  //G4int ParentID = theTrack->GetParentID();
  G4double edepStep = aStep->GetTotalEnergyDeposit();
  //G4double Xpos= aStep->GetPostStepPoint()->GetPosition().x()/mm;
   // G4double Ypos = aStep->GetPostStepPoint()->GetPosition().y()/mm;
    //G4double Zpos = aStep->GetPostStepPoint()->GetPosition().z()/mm;
    G4String processN = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4double kine=theTrack->GetKineticEnergy();
    G4String name= theTrack->GetVolume()->GetName();

    //获取二次粒子信息
    //const std::vector<const G4Track*>*fSecondary = aStep->GetSecondaryInCurrentStep();
   //size_t nbtrk = (*fSecondary).size();
//if (nbtrk) {fseckine=(*fSecondary)[0]->GetKineticEnergy();}


    
    /*size_t nbtrk = (*fSecondary).size();
if (nbtrk) {
  for (size_t lp=0; lp<(*fSecondary).size(); lp++) 
  {(*fSecondary)[lp]->GetKineticEnergy();}
}*/
 
	G4String postVolume = "NULL";
	G4String preVolume = "NULL_pre";

	if(aStep->GetTrack() ->GetNextVolume())//判断粒子是否在世界里
/*{if(edepStep>0&&name=="scater")
{fEventAction->Add(edepStep);}*/
	
  {if(edepStep>0&&name=="scater"&&TrackID>=TrackIDold)
 {E1+=edepStep;}
 if(TrackID<TrackIDold)
 {fstream datafiletrack;
   G4String filename = "Results.txt";
           datafiletrack.open("Results.txt",ios::out|ios::app);
   datafiletrack<<E1<<endl;
   E1=0;}
   if(TrackID<TrackIDold&&edepStep>0&&name=="scater")
   {E1=edepStep;}
   TrackIDold=TrackID;

  
    
    //fstream datafiletrack;
   //G4String filename = "Results.txt";
           // datafiletrack.open("Results.txt",ios::out|ios::app);
   //datafiletrack<<eventID<<"\t"<<TrackID<<"\t"<<Xpos<<"\t"<<Ypos<< "\t"<<Zpos<<"\t"<<edepStep<< "\t"<<kine<< "\t"
   //<<fseckine<<"\t"<<name<<"\t"<<processN<<endl;
    //datafiletrack.close();}
		
	}
//postVolume = fpPostStepPoint ->GetPhysicalVolume() ->GetName();//获取粒子所在体的名字并赋给volume，用于判断粒子位置
	//	preVolume = fpPreStepPoint ->GetPhysicalVolume() ->GetName();
  //G4String matname = fpPreStepPoint->GetMaterial()->GetName(); 

  // if(matname =="mCdZnTe")//&& ParentID !=0)
  // {

 //if((matname =="scater_mat")||(matname =="absorb_mat"))  //获取的是材料的名字，即后面双引号中的“name” ；
  //{

//  if(matname =="lAr")//&& ParentID !=0)
//   {

    //G4int copyNo = aStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();  
    /*G4ThreeVector Copy_position = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetObjectTranslation();

    G4double Copy_positionx = Copy_position.x()/mm;
    G4double Copy_positiony = Copy_position.y()/mm;
    G4double Copy_positionz = Copy_position.z()/mm;*/

    //G4int label_j =copyNo%40;
    
    //if(edepStep>0.) fEventAction->AddE(edepStep);  
   /*G4String processN = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4double edepStep = aStep->GetTotalEnergyDeposit()/keV;
    G4double Xpos= aStep->GetPreStepPoint()->GetPosition().x()/mm;
    G4double Ypos = aStep->GetPreStepPoint()->GetPosition().y()/mm;
    G4double Zpos = aStep->GetPreStepPoint()->GetPosition().z()/mm;*/
    //G4cout<<"eventID"<<"Xpos"<<"Ypos"<<"Zpos"<<"edepStep"<<endl;
  /* if(edepStep>0)
  {fstream datafiletrack;
   G4String filename = "Results.txt";
            datafiletrack.open("Results.txt",ios::out|ios::app);
   datafiletrack<<eventID<<"\t"<<TrackID<<"\t"<<copyNo<<"\t"<<Xpos<<"\t"<<Ypos<< "\t"<<Zpos<<"\t"<<edepStep<<endl;
    datafiletrack.close();}*/
  


  

    /*fEventAction->GetPositionX_track(Xpos, copyNo);
    fEventAction->GetPositionY_track(Ypos, copyNo);
    fEventAction->GetPositionZ_track(Zpos, copyNo);
    fEventAction->GetPositionX_Copy(Copy_positionx, copyNo);
    fEventAction->GetPositionY_Copy(Copy_positiony, copyNo);
    fEventAction->GetPositionZ_Copy(Copy_positionz, copyNo);

    fEventAction->GetCopynum(copyNo);
    fEventAction->AddEdep_track(edepStep, copyNo);*/

 
  /*
    fstream dataFile;
    G4String filename = "Results.txt";
    dataFile.open(filename,ios::out|ios::app);
    if (edepStep>0)											                               // step沉积的能量
    {
        dataFile << eventID <<"\t"<< copyNo << "\t"<< Xpos << "\t" << Ypos << "\t" << Zpos <<  "\t" << edepStep <<endl;
    }
    dataFile.close();
*/
    /*
		G4double cos  = fpPostStepPoint->GetMomentumDirection().z();
		G4double angle = acos(cos)/3.1415926*180.0;     
    */
    /*
    fEventAction->GetPositionx(Xpos, label_i, label_j);  
    fEventAction->GetPositiony(Ypos, label_i, label_j);  
    fEventAction->GetPositionz(Zpos, label_i, label_j);  
    fEventAction->Detectorlabel_i = label_i;
    fEventAction->Detectorlabel_j = label_j;
    */
  


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......