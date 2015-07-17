#ifndef DETECTORCONSTRUCTION_H_
#define DETECTORCONSTRUCTION_H_

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

	virtual G4VPhysicalVolume* Construct();

private:
	G4bool  fCheckOverlaps;
	void DefineMaterials();
	void ConstructSDandField();
};

#endif /* DETECTORCONSTRUCTION_H_ */
