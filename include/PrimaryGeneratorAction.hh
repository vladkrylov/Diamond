#ifndef PRIMARYGENERATORACTION_HH_
#define PRIMARYGENERATORACTION_HH_

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
	double lambda;

	PrimaryGeneratorMessenger* gunMessenger;
	G4ParticleGun* fParticleGun;

	G4ParticleDefinition* FindParticle(G4String particleName);
	bool ToDetector(double x, double y, double z);

	double kinEnergy;
	double Px, Py, Pz;
	double x0, y0, z0;


	TFile* f;
	TTree* t1;
};

#endif /* PRIMARYGENERATORACTION_HH_ */
