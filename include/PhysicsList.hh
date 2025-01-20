#ifndef ENX01_PHYSICS_LIST_H
#define ENX01_PHYSICS_LIST_H

#include "G4VModularPhysicsList.hh"

namespace ENX01 
{
	class PhysicsList : public G4VModularPhysicsList
	{
	public:
		PhysicsList();
	virtual ~PhysicsList();
	virtual void ConstructParticle() override;
	virtual void ConstructProcess() override;
	};
}

#endif