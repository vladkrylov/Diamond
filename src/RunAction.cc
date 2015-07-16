#include "g4csv.hh"
#include "G4Run.hh"

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"

RunAction::RunAction()
: G4UserRunAction()
{
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

void BeginOfRunAction(const G4Run* run)
{
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


