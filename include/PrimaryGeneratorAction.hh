#ifndef ENX01_PRIMARY_GENERATOR_ACTION_H
#define ENX01_PRIMARY_GENERATOR_ACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"

namespace ENX01
{
	class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
	{
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();
	virtual void GeneratePrimaries(G4Event*);
	G4ParticleGun* fParticleGun;
	};
}

#endif 
