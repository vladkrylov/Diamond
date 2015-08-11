#include <ctime>

#include "g4csv.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

RunAction::RunAction()
: G4UserRunAction()
{
	systime = time(NULL);

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetFirstHistoId(1);

    analysisManager->CreateNtuple("DD", "Edep and Ekin");
    analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
	bool autoSeed = true;
	if (autoSeed) {
		// automatic (time-based) random seeds for each run
		G4cout << "*******************" << G4endl;
		G4cout << "*** AUTOSEED ON ***" << G4endl;
		G4cout << "*******************" << G4endl;
		long seeds[2];
		//time_t systime = time(NULL);
		seeds[0] = (long) systime;
		seeds[1] = (long) (systime*G4UniformRand());
		G4Random::setTheSeeds(seeds);
		G4Random::showEngineStatus();
	} else {
		G4Random::showEngineStatus();
	}

	//inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Open an output file
     analysisManager->OpenFile("results.csv");
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    // print histogram statistics
    //
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

}


