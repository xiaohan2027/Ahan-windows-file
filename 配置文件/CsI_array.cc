/*
 * @Begin: *********************************
 * @Author: Liuchangqi
 * @Company: LZU
 * @Date: 2020-03-23 08:31:16
 * @LastEditTime: 2020-05-05 16:32:13
 * @Email: liuchq16@lzu.edu.cn
 * @Descripttion: 
 * @End:   *********************************
 */

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "time.h"
#include "G4Timer.hh"
#include "G4PhysListFactory.hh"
#include "G4PhysicsListHelper.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif


#ifdef G4VIS_USE
 #include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)          //在VS中，argc默认值为1（不输入参数），代表输入参数的个数
{

G4Timer myTimer;
myTimer.Start();

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);       //输入参数，则argc=2，则ui=0
  }

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  DetectorConstruction* det= new DetectorConstruction;
  runManager->SetUserInitialization(det);

  auto thePL = new FTFP_BERT;
	thePL->ReplacePhysics(new G4EmStandardPhysics_option4());
  runManager->SetUserInitialization(thePL);
  // Physics list - GEORGE
  /*
  G4String plname = "QBBC_EMZ";
  G4PhysListFactory plfactory;
  G4VModularPhysicsList* physicsList = plfactory.GetReferencePhysList(plname);

  G4StepLimiterPhysics* StepLim = new G4StepLimiterPhysics(); //George
  StepLim->SetApplyToAll(true); //George 
  physicsList->RegisterPhysics(StepLim); //George

  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
  */
  /*
  PhysicsList* phys = new PhysicsList;
  runManager->SetUserInitialization(phys);
  */    
  runManager->SetUserInitialization(new ActionInitialization()); 
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode 批处理
    G4String command = "/control/execute ";
    G4String fileName = argv[1];                   //argv[1]指向在命令行中执行程序名后的第一个字符串 
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode 交互界面
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
 myTimer.Stop();
 G4cout << "run time:"<<myTimer << G4endl; 

  delete visManager;
  delete runManager;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
