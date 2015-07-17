#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
, fParticleGun(0)
{
	Emean = 2.5*MeV;
	sigma = 0.2*MeV;

	poisson = new std::poisson_distribution<int>(4.3);
	gauss = new std::normal_distribution<double>(Emean, sigma);

	fParticleGun = new G4ParticleGun();
	fParticleGun->SetNumberOfParticles(1);
	fParticleGun->SetParticleDefinition(FindParticle("e-"));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1*mm));
	fParticleGun->SetParticleEnergy(Emean);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
	delete poisson;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	int N = (*poisson)(generator);
	for (int i = 0; i < 9; ++i) {
		fParticleGun->SetParticleEnergy((*gauss)(generator));
		fParticleGun->GeneratePrimaryVertex(event);
	}
}

G4ParticleDefinition* PrimaryGeneratorAction::FindParticle(G4String particleName)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	return particle;
}
