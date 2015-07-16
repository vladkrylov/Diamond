#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
, fParticleGun(0)
{
	fParticleGun = new G4ParticleGun();
	fParticleGun->SetNumberOfParticles(1);
	fParticleGun->SetParticleDefinition(FindParticle("e-"));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1*mm));
	fParticleGun->SetParticleEnergy(2.5*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	fParticleGun->GeneratePrimaryVertex(event);
}

G4ParticleDefinition* PrimaryGeneratorAction::FindParticle(G4String particleName)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	return particle;
}
