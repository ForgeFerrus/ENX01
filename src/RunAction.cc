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
	{ // ��������� ����������
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->SetDefaultFileType("root");
        analysisManager->SetNtupleMerging(true);
        analysisManager->SetVerboseLevel(0);
        analysisManager->SetFileName("EnergySpectrum");
    // ����������� ����� RunAction ��������� �������� ������
    const G4int ntupleId1 = analysisManager->CreateNtuple("Absolute Energies", "Gamma Energies");
        analysisManager->CreateNtupleDColumn(ntupleId1, "AbsEnergy");
        analysisManager->FinishNtuple(ntupleId1);
    const G4int ntupleId2 = analysisManager->CreateNtuple("Relative Energies", "Gamma Energies");
        analysisManager->CreateNtupleDColumn(ntupleId2, "RelEnergy");
        analysisManager->FinishNtuple(ntupleId2);
    }
    RunAction::~RunAction() {
    // ������ ������� ����������
    auto analysisManager = G4AnalysisManager::Instance();
        delete analysisManager;
    }
    void RunAction::BeginOfRunAction(const G4Run* aRun)
    {
    // ³������� ����� ��� ��������� �����
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->OpenFile();
    }
    void RunAction::EndOfRunAction(const G4Run* aRun)
    {
    // ����� � �������� ����� � ������
    auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->Write();
        analysisManager->CloseFile();
    }
}
