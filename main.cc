#include <G4RunManager.hh>
#include <G4UImanager.hh>

#include "ExN01DetectorConstruction.hh"
#include "ExN01PhysicsList.hh"
#include "ExN01PrimaryGeneratorAction.hh"
int main()
{
 // construct the default run manager
 G4RunManager* runManager = new G4RunManager;
 // set mandatory initialization classes
 runManager->SetUserInitialization(new ExN01DetectorConstruction);
 runManager->SetUserInitialization(new ExN01PhysicsList);
 // set mandatory user action class
 runManager->SetUserAction(new ExN01PrimaryGeneratorAction);
 // initialize G4 kernel
 runManager->initialize();
 // get the pointer to the UI manager and set verbosities
 G4UImanager* UI = G4UImanager::GetUIpointer();
 UI->ApplyCommand("/run/verbose 1");
 UI->ApplyCommand("/event/verbose 1");
 UI->ApplyCommand("/tracking/verbose 1");
 // start a run
 
 G4UIsession* session = new G4UIterminal;
    session->SessionStart();
    delete session;
 int numberOfEvent = 3;
 runManager->BeamOn(numberOfEvent);
 // job termination
 delete runManager;
 return 0;
}