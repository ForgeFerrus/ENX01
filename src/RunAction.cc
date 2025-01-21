#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleGun.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

namespace ENX01
{
    RunAction::RunAction()
	{ // Створення аналізатора
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->SetDefaultFileType("root");
        analysisManager->SetNtupleMerging(true);
        analysisManager->SetVerboseLevel(0);
        analysisManager->SetFileName("EnergySpectrum");
    // Конструктор класу RunAction налаштовує менеджер аналізу
    const G4int ntupleId1 = analysisManager->CreateNtuple("Absolute Energies", "Gamma Energies");
        analysisManager->CreateNtupleDColumn(ntupleId1, "AbsEnergy");
        analysisManager->FinishNtuple(ntupleId1);
    const G4int ntupleId2 = analysisManager->CreateNtuple("Relative Energies", "Gamma Energies");
        analysisManager->CreateNtupleDColumn(ntupleId2, "RelEnergy");
        analysisManager->FinishNtuple(ntupleId2);
    }
    RunAction::~RunAction() {
    // Чистка ресурсів аналізатора
    auto analysisManager = G4AnalysisManager::Instance();
        delete analysisManager;
    }
    void RunAction::BeginOfRunAction(const G4Run* aRun)
    {
    // Відкриття файлу для зберігання даних
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->OpenFile();
    }
    void RunAction::EndOfRunAction(const G4Run* aRun)
    {
    // Запис і закриття файлу з даними
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile();
    }
}
