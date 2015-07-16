/*
 * EventAction.hh
 *
 *  Created on: Jul 16, 2015
 *      Author: vlad
 */

#ifndef EVENTACTION_HH_
#define EVENTACTION_HH_

#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction();
	virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

private:
    G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                            const G4Event* event) const;
    G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
    void PrintEventStatistics(G4double Edep) const;

    G4int  fEdepHCID;
};

#endif /* EVENTACTION_HH_ */
