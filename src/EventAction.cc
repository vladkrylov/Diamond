#include "g4csv.hh"
#include "G4SDManager.hh"

#include "G4RunManager.hh"
#include "EventAction.hh"
#include "G4Event.hh"

EventAction::EventAction()
: G4UserEventAction(),
fEdepHCID(-1)
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* event)
{
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    // Get hist collections IDs
    if ( fEdepHCID == -1 ) {
        fEdepHCID
        = G4SDManager::GetSDMpointer()->GetCollectionID("DD/Edep");
    }

    // Get sum values from hits collections
    //
    G4double Edep = GetSum(GetHitsCollection(fEdepHCID, event));


    // get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // fill ntuple
    //
    analysisManager->FillNtupleDColumn(0, Edep);
    analysisManager->AddNtupleRow();
}

G4THitsMap<G4double>*
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
    G4THitsMap<G4double>* hitsCollection
    = static_cast<G4THitsMap<G4double>*>(event->GetHCofThisEvent()->GetHC(hcID));

    if ( ! hitsCollection ) {
        G4ExceptionDescription msg;
        msg << "Cannot access hitsCollection ID " << hcID;
        G4Exception("EventAction::GetHitsCollection()",
                    "MyCode0003", FatalException, msg);
    }

    return hitsCollection;
}

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
    G4double sumValue = 0;
    std::map<G4int, G4double*>::iterator it;
    for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
        sumValue += *(it->second);
    }
    return sumValue;
}
