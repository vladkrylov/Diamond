#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"

#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
, fCheckOverlaps(true)
{

}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	G4String name;

	G4double z,a, density;
	density=3.52*g/cm3;
	a=12.01074*g/mole;
	G4Material* DD_mat = new G4Material(name="diamond",z=6.,a,density);

	G4NistManager* man = G4NistManager::Instance();
	G4Material* Air = man->FindOrBuildMaterial("G4_Galactic");

	//
	// World
	//
	G4double world_size = 14*cm;

	G4Box* solidWorld =
	new G4Box("World",                       //its name
			  0.5*world_size, 0.5*world_size, 0.5*world_size); //its size

	G4LogicalVolume* logicWorld =
	new G4LogicalVolume(solidWorld,          //its solid
						Air,         		 //its material
						"World");            //its name

	G4VPhysicalVolume* physWorld =
	new G4PVPlacement(0,                     //no rotation
					  G4ThreeVector(),       //at (0,0,0)
					  logicWorld,            //its logical volume
					  "World",               //its name
					  0,                     //its mother  volume
					  false,                 //no boolean operation
					  0,                     //copy number
					  fCheckOverlaps);       // checking overlaps

	//
	// DD
	//
	G4double thickness = 500*um;
	G4double width = 4*mm;
	G4double height = 4*mm;

	G4Box* solidDD =
	new G4Box("DD", 0.5*height, 0.5*width, 0.5*thickness);

	G4LogicalVolume* logicDD =
	new G4LogicalVolume(solidDD,
						DD_mat,
						"DDLV");

	new G4PVPlacement(0,
				  G4ThreeVector(),
				  logicDD,
				  "DD",
				  logicWorld,
				  false,
				  0,
				  fCheckOverlaps);

	// Print materials
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;

	//always return the physical World
	//
	return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    // declare DD as a MultiFunctionalDetector scorer
    //
    G4MultiFunctionalDetector* dd = new G4MultiFunctionalDetector("DD");
    G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("Edep");
    dd->RegisterPrimitive(primitiv1);
    SetSensitiveDetector("DDLV",dd);
}


