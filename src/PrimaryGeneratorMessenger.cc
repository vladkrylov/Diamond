#include "G4UIcmdWithADouble.hh"

#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
: Action(Gun)
{
	gunDir = new G4UIdirectory("/diamond/source/");
	gunDir->SetGuidance("PrimaryGenerator control");

	lambdaCmd = new G4UIcmdWithADouble("/diamond/source/lambda", this);
	lambdaCmd -> SetGuidance("lambda parameter of Poisson distributed number of particles");
	lambdaCmd -> SetParameterName("lambda", false);
	lambdaCmd -> SetRange("lambda>=0.");
	lambdaCmd -> AvailableForStates(G4State_Idle);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
	delete lambdaCmd;
	delete gunDir;
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

	if( command == lambdaCmd ){
		Action->SetLambda(lambdaCmd->GetNewDoubleValue(newValue));
	}
}


