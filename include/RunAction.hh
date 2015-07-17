#ifndef INCLUDE_RUNACTION_HH_
#define INCLUDE_RUNACTION_HH_

#include "globals.hh"
#include "G4UserRunAction.hh"

class RunAction: public G4UserRunAction {
public:
	RunAction();
	virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

private:
    time_t systime;
};

#endif /* INCLUDE_RUNACTION_HH_ */
