#include <cmath>

#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4Poisson.hh"
#include "Randomize.hh"

#include "TFile.h"
#include "TTree.h"

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorMessenger.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
, fParticleGun(0)
, lambda(1.)
{
	gunMessenger = new PrimaryGeneratorMessenger(this);

	// open ROOT file for reading source parameters
	f = new TFile("Result.root");
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
	delete gunMessenger;
	delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
	int N = G4Poisson(lambda);
	int nEntries = t1->GetEntries();
	int eventId;
	double x, y, z; // position of primary vertex

	for (int i = 0; i < N; ++i) {
		eventId = (int) (nEntries*G4UniformRand());
		t1->GetEntry(eventId);
		x = x0*mm - 20.3*cm;
		y = y0*mm;
		z = z0;

		if (ToDetector(x, y, z)) {
			fParticleGun->SetParticleEnergy(kinEnergy*MeV);
			fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));
			fParticleGun->SetParticleMomentumDirection(G4ThreeVector(Px, Py, Pz));
			fParticleGun->GeneratePrimaryVertex(event);
		} else continue;
	}
}

G4ParticleDefinition* PrimaryGeneratorAction::FindParticle(G4String particleName)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	return particle;
}

void PrimaryGeneratorAction::SetLambda(double val)
{
	lambda = val;
}

bool PrimaryGeneratorAction::ToDetector(double x, double y, double z)
{
	// diamond parameters
	// TODO get them from DetectorConstruction
	G4ThreeVector ddCenter(0, 0, 0);
	double thickness = 500*um;
	double width = 4*mm;
	double height = 4*mm;

	double z_target = ddCenter.z() + thickness/2;
	// distance OZ from source to face of diamond
	double dz = z - z_target;

	// translation of particle
	G4ThreeVector translation(Px, Py, Pz);
	translation = translation / translation.z() * dz;

	double x_target = x - translation.x();
	double y_target = y - translation.y();

	if ((fabs(x_target) <= width/2)
	 && (fabs(y_target) <= height/2)) {
		G4cout << x << "    " << y << "    " << z << "    " << G4endl;
		G4cout << x_target << "    " << y_target << "    " << z_target << "    " << G4endl;
		G4cout << "============================================================" << G4endl;
		return true;
	} else return false;
}
