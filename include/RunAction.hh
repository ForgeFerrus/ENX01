#ifndef ENX01_RUN_ACTION_HH
#define ENX01_RUN_ACTION_HH

#include "G4UserRunAction.hh"

#include "G4AnalysisManager.hh"


namespace ENX01
{
	class HitsCollection;
	class RunAction : public G4UserRunAction {
	public:
		RunAction();
		~RunAction();
	void BeginOfRunAction(const G4Run* aRun) override;
	void EndOfRunAction(const G4Run* aRun) override;
	};
}

#endif // !G4_BREMS_RUN_ACTION_HH
