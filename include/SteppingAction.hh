#ifndef ENX01_STEPPING_ACTION_H
#define ENX01_STEPPING_ACTION_H

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

namespace ENX01 
{
	class SteppingAction : public G4UserSteppingAction 
	{
	public:
		SteppingAction();
		~SteppingAction();

	void UserSteppingAction(const G4Step*);
	private:
		G4LogicalVolume* fBremsVolume = nullptr;
	};
}

#endif // !G4_BREMS_STEPPING_ACTION_H
