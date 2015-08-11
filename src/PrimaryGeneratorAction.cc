#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

#include "TFile.h"
#include "TTree.h"

#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
, fParticleGun(0)
{
	poisson = new std::poisson_distribution<int>(4.3);

	// open ROOT file for reading source parameters
	f = new TFile("/home/vlad/10g4work/LeetechRuns/DiamondSource100um/Result.root");
	t1 = (TTree*)f->Get("T");
	t1->SetBranchAddress("Energy", &kinEnergy);
	t1->SetBranchAddress("PX", &Px);
	t1->SetBranchAddress("PY", &Py);
	t1->SetBranchAddress("PZ", &Pz);
	t1->SetBranchAddress("PosX", &x0);
	t1->SetBranchAddress("PosY", &y0);
	z0 = 5*cm;

	fParticleGun = new G4ParticleGun();
	fParticleGun->SetNumberOfParticles(1);
	fParticleGun->SetParticleDefinition(FindParticle("e-"));
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

	fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*cm));
	fParticleGun->SetParticleEnergy(16.*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
	delete poisson;
	delete gauss;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	int N = (*poisson)(generator);
	int eventId;
	for (int i = 0; i < N; ++i) {
		eventId = (int) (t1->GetEntries()*G4UniformRand());
		t1->GetEntry(eventId);
		fParticleGun->SetParticleEnergy(kinEnergy*MeV);
		fParticleGun->SetParticlePosition(G4ThreeVector(x0*mm - 20.3*cm, y0*mm, z0));
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector(Px, Py, Pz));
		fParticleGun->GeneratePrimaryVertex(event);
	}
}

G4ParticleDefinition* PrimaryGeneratorAction::FindParticle(G4String particleName)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	return particle;
}
