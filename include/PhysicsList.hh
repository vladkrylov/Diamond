#ifndef PHYSICSLIST_HH_
#define PHYSICSLIST_HH_

#include "globals.hh"
#include "G4VUserPhysicsList.hh"

class PhysicsList : public G4VUserPhysicsList
{
public:
	PhysicsList();
	virtual ~PhysicsList();

private:
	// Construct particle and physics process
	void ConstructParticle();
	void ConstructProcess();

	void ConstructEM();
	void ConstructDecay();
};

#endif /* PHYSICSLIST_HH_ */
