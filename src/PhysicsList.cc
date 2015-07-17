#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

#include "PhysicsList.hh"

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
	// Default physics
	RegisterPhysics(new G4DecayPhysics());

	// Radioactive decay
	RegisterPhysics(new G4RadioactiveDecayPhysics());

	// EM physics
	RegisterPhysics(new G4EmStandardPhysics());
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
