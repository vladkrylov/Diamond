#include "G4PhysicsListHelper.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4ionIonisation.hh"
#include "G4Decay.hh"
#include "G4StepLimiter.hh"
#include "G4KleinNishinaModel.hh"
#include "G4SystemOfUnits.hh"
#include "G4NuclearStopping.hh"
#include "G4IonParametrisedLossModel.hh"

#include "PhysicsList.hh"

PhysicsList::PhysicsList()
: G4VUserPhysicsList()
{
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::ConstructParticle()
{
	// In this method, static member functions should be called
	// for all particles which you want to use.
	// This ensures that objects of these particle types will be
	// created in the program.

	G4BosonConstructor  pBosonConstructor;
	pBosonConstructor.ConstructParticle();

	G4LeptonConstructor pLeptonConstructor;
	pLeptonConstructor.ConstructParticle();

	G4MesonConstructor pMesonConstructor;
	pMesonConstructor.ConstructParticle();

	G4BaryonConstructor pBaryonConstructor;
	pBaryonConstructor.ConstructParticle();

	G4IonConstructor pIonConstructor;
	pIonConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
	ConstructDecay();
}

void PhysicsList::ConstructEM()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // Add standard EM Processes
  //
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {

      ////ph->RegisterProcess(new G4RayleighScattering, particle);
      ph->RegisterProcess(new G4PhotoElectricEffect, particle);
      G4ComptonScattering* cs   = new G4ComptonScattering;
      cs->SetEmModel(new G4KleinNishinaModel());
      ph->RegisterProcess(cs, particle);
      ph->RegisterProcess(new G4GammaConversion, particle);

    } else if (particleName == "e-") {

      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      //
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.1, 100*um);
      ph->RegisterProcess(eIoni, particle);
      //
      ph->RegisterProcess(new G4eBremsstrahlung(), particle);

    } else if (particleName == "e+") {

      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      //
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.1, 100*um);
      ph->RegisterProcess(eIoni, particle);
      //
      ph->RegisterProcess(new G4eBremsstrahlung(), particle);
      //
      ph->RegisterProcess(new G4eplusAnnihilation(), particle);

    } else if (particleName == "mu+" ||
               particleName == "mu-"    ) {

      ph->RegisterProcess(new G4MuMultipleScattering(), particle);
      G4MuIonisation* muIoni = new G4MuIonisation();
      muIoni->SetStepFunction(0.1, 50*um);
      ph->RegisterProcess(muIoni, particle);
      ph->RegisterProcess(new G4MuBremsstrahlung(), particle);
      ph->RegisterProcess(new G4MuPairProduction(), particle);

    } else if( particleName == "proton" ||
               particleName == "pi-" ||
               particleName == "pi+"    ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.1, 20*um);
      ph->RegisterProcess(hIoni, particle);
      ph->RegisterProcess(new G4hBremsstrahlung(), particle);
      ph->RegisterProcess(new G4hPairProduction(), particle);

    } else if( particleName == "alpha" ||
               particleName == "He3"    ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetStepFunction(0.1, 1*um);
      ph->RegisterProcess(ionIoni, particle);
      ph->RegisterProcess(new G4NuclearStopping(), particle);

    } else if( particleName == "GenericIon" ) {

      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ionIoni->SetStepFunction(0.1, 1*um);
      ph->RegisterProcess(ionIoni, particle);
      ph->RegisterProcess(new G4NuclearStopping(), particle);

    } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) &&
               (particle->GetParticleName() != "chargedgeantino")) {

      //all others charged particles except geantino
      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      ph->RegisterProcess(new G4hIonisation(), particle);
    }
  }
}

void PhysicsList::ConstructDecay()
{
	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

	// Add Decay Process
	G4Decay* theDecayProcess = new G4Decay();
	theParticleIterator->reset();
	while( (*theParticleIterator)() ) {
		G4ParticleDefinition* particle = theParticleIterator->value();
		if (theDecayProcess->IsApplicable(*particle)) {
			ph->RegisterProcess(theDecayProcess, particle);
		}
	}
}


