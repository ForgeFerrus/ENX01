
#include <ActionInitialization.hh>
#include <PrimaryGeneratorAction.hh>
#include <SteppingAction.hh>

#include "RunAction.hh"
#include "G4Event.hh"
#include "G4UserEventAction.hh"
//#include "EventAction.hh"
namespace ENX01
{
// ����������� ����� ActionInitialization
ActionInitialization::ActionInitialization() 
: G4VUserActionInitialization() 
{ } // ���������� ����� ActionInitialization
ActionInitialization::~ActionInitialization()
{ } // ����������� �� ��� ������� ������
	void ActionInitialization::Build() 
	const {
		SetUserAction(new PrimaryGeneratorAction);
		SetUserAction(new RunAction());
		SetUserAction(new EventAction());
		SetUserAction(new SteppingAction());
	};
	// ����������� �� ��� ��������� ������
	void ActionInitialization::BuildForMaster() 
	const {
		SetUserAction(new RunAction());
	}
	// ����������� ����� EventAction
	EventAction::EventAction() {
	}
	// ���������� ����� EventAction 
	EventAction::~EventAction() {
	} // ĳ� �� ������� ����� ��䳿
	void EventAction::BeginOfEventAction(const G4Event* event) {
	} // ĳ� � ���� ����� ��䳿
	void EventAction::EndOfEventAction(const G4Event* event) {
	}
}