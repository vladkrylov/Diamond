#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

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
}
