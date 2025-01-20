#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"

namespace ENX01 {
	PhysicsList::PhysicsList() : G4VModularPhysicsList() {
	RegisterPhysics(new G4EmStandardPhysics());
	}
	PhysicsList::~PhysicsList() {}
void PhysicsList::ConstructParticle() {
	G4VModularPhysicsList::ConstructParticle();
	}
void PhysicsList::ConstructProcess() {
	G4VModularPhysicsList::ConstructProcess();
    }
}