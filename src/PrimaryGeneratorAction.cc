#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include <PrimaryGeneratorAction.hh>

namespace ENX01
{
	PrimaryGeneratorAction::PrimaryGeneratorAction() {
		// set up particle gun
		G4int nParticles = 1;
		fParticleGun = new G4ParticleGun(nParticles);

		// define particle properties
		const G4String& particleName = "e-";

		// Find the particle (e-) in the G4Particle table
		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle
			= particleTable->FindParticle(particleName);

		// Set the particle type to the particle gun
		fParticleGun->SetParticleDefinition(particle);

		// set the particle's direction:
		G4ThreeVector momentumDirection = G4ThreeVector(0, 0, 1);
		fParticleGun->SetParticleMomentumDirection(momentumDirection);

		// set the particle's energy:
		G4double energy = 1.0 * MeV; // Define the energy value
		fParticleGun->SetParticleEnergy(energy);
	}
	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}
	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
	{
		// Randomize x and y starting point within a 1 mm diameter
		G4double radius = .5 * mm;
		// generate random x and y positions within that radius
		double x, y;
		// to avoid using slow methods like sin and cos,
		// we generate random values in a square and regect the ones
		// outside of a circle.
		do {
			x = G4UniformRand() * (1.0 * radius) - radius;
			y = G4UniformRand() * (1.0 * radius) - radius;
		} while (x * x + y * y > radius * radius);

		G4ThreeVector position = G4ThreeVector(x, y, -2.5 * cm);
		fParticleGun->SetParticlePosition(position);
		// satisfy "generate primaries" here.
		fParticleGun->GeneratePrimaryVertex(event);
	}
} // namespace ENX01