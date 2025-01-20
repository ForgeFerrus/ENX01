#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4RunManagerFactory.hh"
#include "G4VisExecutive.hh"
#include <iostream>

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

namespace ENX01 {
    using namespace std;

    int main(int argc, char** argv) {
        // Ініціалізувати інтерфейс користувача
        G4UIExecutive* ui = nullptr;
        if (argc == 1) {
            ui = new G4UIExecutive(argc, argv);
        }
        // створити менеджер виконання за замовчуванням
        auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
        // встановити 3 необхідні класи ініціалізації
        runManager->SetUserInitialization(new DetectorConstruction());
        runManager->SetUserInitialization(new PhysicsList());
        runManager->SetUserInitialization(new ActionInitialization());
        // ІНШІ КЛАСИ:
        // Vismanager, scoringmanager тощо.
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        long seed = 1;
        CLHEP::HepRandom::setTheSeed(seed);
        G4Random::setTheSeed(seed);
        // START UI 
        // отримати покажчик на UI менеджер
        G4UImanager* UImanager = G4UImanager::GetUIpointer();
        // Виконати макрос або запустити інтерфейс користувача
        if (!ui) {
            // пакетний режим
            G4String command = "/control/execute run.mac";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command + fileName);
        }
        else {
            // запустити візуалізацію
            UImanager->ApplyCommand("/control/execute vis.mac");
            // використовувати UI
            ui->SessionStart();
            delete ui;
        }
        // очистити
        delete visManager;
        delete runManager;
        return 0;
    }
}

int main(int argc, char** argv) {
    return ENX01::main(argc, argv);
}
