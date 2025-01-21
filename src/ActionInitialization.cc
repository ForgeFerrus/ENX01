
#include <ActionInitialization.hh>
#include <PrimaryGeneratorAction.hh>
#include <SteppingAction.hh>

#include "RunAction.hh"
#include "G4Event.hh"
#include "G4UserEventAction.hh"
//#include "EventAction.hh"
namespace ENX01
{
// Конструктор класу ActionInitialization
ActionInitialization::ActionInitialization() 
: G4VUserActionInitialization() 
{ } // Деструктор класу ActionInitialization
ActionInitialization::~ActionInitialization()
{ } // Ініціалізація дій для кожного потоку
	void ActionInitialization::Build() 
	const {
		SetUserAction(new PrimaryGeneratorAction);
		SetUserAction(new RunAction());
		SetUserAction(new EventAction());
		SetUserAction(new SteppingAction());
	};
	// Ініціалізація дій для головного потоку
	void ActionInitialization::BuildForMaster() 
	const {
		SetUserAction(new RunAction());
	}
	// Конструктор класу EventAction
	EventAction::EventAction() {
	}
	// Деструктор класу EventAction 
	EventAction::~EventAction() {
	} // Дії на початку кожної події
	void EventAction::BeginOfEventAction(const G4Event* event) {
	} // Дії в кінці кожної події
	void EventAction::EndOfEventAction(const G4Event* event) {
	}
}