#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"

namespace ENX01 {
	PhysicsList::PhysicsList() : G4VModularPhysicsList() 
	{ // Реєстрація електромагнітних процесів
	RegisterPhysics(new G4EmStandardPhysics());
	// Додаткові фізичні пакети можна додавати тут 
	// RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
	} //Конструктор ініціалізує G4VModularPhysicsList та реєструє стандартний електромагнітний фізичний пакет
	PhysicsList::~PhysicsList() { // Виклик базового методу для конструкції частинок
	} //Деструктор не робить нічого особливого, оскільки автоматично звільняються зареєстровані фізичні пакети
void PhysicsList::ConstructParticle() {
	G4VModularPhysicsList::ConstructParticle();
	} //Викликається базовий метод для конструкції частинок
void PhysicsList::ConstructProcess() {
	G4VModularPhysicsList::ConstructProcess();
    } //Викликає базовий метод G4VModularPhysicsList для конструкції процесів
} // Додаткові процеси можна додавати тут 
  // AddTransportation();