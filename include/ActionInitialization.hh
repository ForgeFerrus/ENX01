#ifndef ENX01_ACTION_INITIALIZATION_H
#define ENX01_ACTION_INITIALIZATION_H

#include "G4VUserActionInitialization.hh"
#include "G4UserEventAction.hh"
#include "G4Event.hh"

namespace ENX01
{
	class ActionInitialization : public G4VUserActionInitialization
	{
	public:
		ActionInitialization();
		virtual	~ActionInitialization();

		void Build() const override;
		void BuildForMaster() const override;
	};
	class EventAction : public G4UserEventAction {
	public:
		EventAction();
		virtual ~EventAction();
		virtual void BeginOfEventAction(const G4Event*);
		virtual void EndOfEventAction(const G4Event*);
	
	bool operator==(const EventAction& other) const = default;
	};
}
#endif // ENX01_ACTION_INITIALIZATION_H