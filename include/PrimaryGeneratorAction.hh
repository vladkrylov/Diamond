#ifndef PRIMARYGENERATORACTION_HH_
#define PRIMARYGENERATORACTION_HH_

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4ParticleGun;
class G4ParticleDefinition;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	virtual ~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4ParticleGun* fParticleGun;

	G4ParticleDefinition* FindParticle(G4String particleName);
};

#endif /* PRIMARYGENERATORACTION_HH_ */
