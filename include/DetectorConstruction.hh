#ifndef ENX01_DETECTOR_CONSTRUCTION_H
#define ENX01_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"

namespace ENX01
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

	G4VPhysicalVolume* Construct() override;
	G4LogicalVolume* GetBremsVolume() const { return fBremsVolume; };

	private:
		G4LogicalVolume* fBremsVolume = nullptr;
		void ConstructSDandField();
		G4VPhysicalVolume* Construct(int argc, char** argv);
	};
}

#endif