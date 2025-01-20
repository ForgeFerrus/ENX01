#ifndef ENX01_ACTION_INITIALIZATION_H
#define ENX01_ACTION_INITIALIZATION_H

#include "G4VUserActionInitialization.hh"

namespace ENX01 
{
	class ActionInitialization : public G4VUserActionInitialization 
	{
	public:
		ActionInitialization() = default;
	virtual	~ActionInitialization() override = default;

	void Build() const override;
	void BuildForMaster() const override;
	};
}
#endif
