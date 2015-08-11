#ifndef PRIMARYGENERATORACTION_HH_
#define PRIMARYGENERATORACTION_HH_

#include <random>

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGeneratorMessenger;
class G4Event;
class G4ParticleGun;
class G4ParticleDefinition;
class TFile;
class TTree;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	virtual ~PrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

	void SetLambda(double lambda);

private:
	double Emean;
	double sigma;

	PrimaryGeneratorMessenger* gunMessenger;
	G4ParticleGun* fParticleGun;
	std::default_random_engine generator;
	std::poisson_distribution<int>* poisson;

	G4ParticleDefinition* FindParticle(G4String particleName);

	double kinEnergy;
	double Px, Py, Pz;
	double x0, y0, z0;


	TFile* f;
	TTree* t1;
};

#endif /* PRIMARYGENERATORACTION_HH_ */
