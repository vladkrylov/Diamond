#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

ActionInitialization::ActionInitialization()
{
	// TODO Auto-generated constructor stub
}

ActionInitialization::~ActionInitialization()
{
	// TODO Auto-generated destructor stub
}

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction);
	SetUserAction(new RunAction);
	SetUserAction(new EventAction);
}
