#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#ifdef G4VIS_USE
	#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
	#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc, char** argv)
{
	// Choose the Random engine
	//
	G4Random::setTheEngine(new CLHEP::RanecuEngine);

	// Construct the default run manager
	//
	G4RunManager* runManager = new G4RunManager;

	// Set mandatory initialization classes
	//
	// Detector construction
	runManager->SetUserInitialization(new DetectorConstruction);

	// Physics list
	runManager->SetUserInitialization(new PhysicsList);

	// User action initialization
	runManager->SetUserInitialization(new ActionInitialization);

	#ifdef G4VIS_USE
		// Initialize visualization
		G4VisManager* visManager = new G4VisExecutive;
		// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
		// G4VisManager* visManager = new G4VisExecutive("Quiet");
		visManager->Initialize();
	#endif

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (argc != 1) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	} else {
		G4cout << "No .mac file specified as an argument. Exit program.";
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted
	// in the main() program !

	#ifdef G4VIS_USE
		delete visManager;
	#endif
	delete runManager;

	return 0;
}
