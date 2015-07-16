/*
 * RunAction.hh
 *
 *  Created on: Jul 16, 2015
 *      Author: vlad
 */

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
};

#endif /* INCLUDE_RUNACTION_HH_ */
