
#include <SteppingAction.hh>
#include <DetectorConstruction.hh>
#include <SensitiveDetector.hh>

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
//Заголовки та простір імен
namespace ENX01
{	//Тут ми включаємо необхідні заголовкові файли для реалізації SteppingAction. Програма знаходиться в просторі імен ENX01.
	SteppingAction::SteppingAction() {
	} //Конструктор та деструктор класу SteppingAction ініціалізують і знищують об'єкти відповідного класу
	SteppingAction::~SteppingAction() {
	}
	void SteppingAction::UserSteppingAction(const G4Step* step) 
	{ //Ця функція викликається на кожному кроці симуляції. Параметр step представляє інформацію про поточний крок
		if (!fBremsVolume) 
		{
	const auto detConstruction = static_cast<const DetectorConstruction*>(
	G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	fBremsVolume = detConstruction->GetBremsVolume();
	} //перевіряємо, чи був встановлений об'єм fBremsVolume. Якщо ні, він отримує його з конструктора детектора
	G4LogicalVolume* currentVolume = step->GetPreStepPoint()->GetTouchableHandle()
			->GetVolume()->GetLogicalVolume();
		if (currentVolume != fBremsVolume) { return; }
	//перевіряємо, чи частка перебуває в об'ємі fBremsVolume. Якщо ні, функція завершується
	G4int absNTupleID = 0;
	G4int relNTupleID = 1;
	G4int nSecondaryParticles = step->GetNumberOfSecondariesInCurrentStep();
		if (nSecondaryParticles == 0) { return; }
	//Перевіряємо кількість вторинних частинок у поточному кроці. Якщо їх немає, функція завершується
	G4double electronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
	const std::vector<const G4Track*>* secondaries
			= step->GetSecondaryInCurrentStep();
		//Отримуємо кінетичну енергію електрона з поточного кроку та список вторинних частинок
		for (int i = 0; i < secondaries->size(); i++) 
		{
		const G4Track* track = (*secondaries)[i];
		G4String particleName = track->GetParticleDefinition()->GetParticleName();
			if (particleName == "gamma")
			{
		G4double energy = track->GetKineticEnergy();
		auto analysisManager = G4AnalysisManager::Instance();
			analysisManager->FillNtupleDColumn(absNTupleID, 0, energy);
			analysisManager->AddNtupleRow(absNTupleID);
		G4double relEnergy = energy / electronEnergy;
			analysisManager->FillNtupleDColumn(relNTupleID, 0, relEnergy);
			analysisManager->AddNtupleRow(relNTupleID);
			} 
		} // Проходимо по списку вторинних частинок та зберігаємо енергію гамма-квантів та їх відношення до енергії електронаЦей цикл обробляє вторинні частинки. Якщо частинка є гамма-квантом ("gamma"), її енергія записується в аналізатор
	//Цей код дозволяє вам збирати дані про вторинні гамма - кванти та їх енергії, що виникають під час симуляції.
	}
}