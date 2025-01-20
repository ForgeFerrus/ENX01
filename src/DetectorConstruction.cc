#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"
#include <SensitiveDetector.hh>
#include <DetectorConstruction.hh>

namespace ENX01 {
    // Будуємо тут наші детектори
    G4VPhysicalVolume* DetectorConstruction::Construct()
    {   // Менеджер матеріалів nist
        G4NistManager* nist = G4NistManager::Instance();
        // Почнемо з побудови світу:
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
        G4bool checkOverlaps = true;
        G4double world_sizeXY = 30 * cm;
        G4double world_sizeZ = 20 * cm;

        G4Box* solidWorld =
            new G4Box("World",
                0.5 * world_sizeXY,
                0.5 * world_sizeXY,
                0.5 * world_sizeZ);

        G4LogicalVolume* logicWorld =
            new G4LogicalVolume(solidWorld,
                vacuum, "World");

        G4VPhysicalVolume* physWorld =
            new G4PVPlacement(0,
                G4ThreeVector(),
                logicWorld,
                "World",
                0,
                false,
                0,
                checkOverlaps);
        // створюємо нашу вольфрамову мішень
        G4Material* det_mat = nist->FindOrBuildMaterial("G4_W");
        G4double innerTargetRadius = 0.0;
        G4double outerTargetRadius = 0.5 * cm;
        G4double targetThickness = 1 * mm;
        G4Tubs* solidTarget = new G4Tubs("Target",
            innerTargetRadius,
            outerTargetRadius,
            targetThickness / 2.0,
            0.0,
            360.0 * deg);

        G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget,
            det_mat,
            "Target");
        // цільове положення та обертання
        G4ThreeVector targetPos = G4ThreeVector(); // 0,0
        G4RotationMatrix* targetRotation = new G4RotationMatrix();
        // розмістити ціль у світі
        new G4PVPlacement(targetRotation,
            targetPos,
            logicTarget,
            "Target",
            logicWorld,
            false,
            0);
        fBremsVolume = logicTarget;

        // Detector
        G4double det_sizeXY = 10 * cm; // Add this line
        G4double det_sizeZ = 5 * cm; // Add this line
        G4Box* solidDet = new G4Box("Detector",
            0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ);

        G4LogicalVolume* logicDet =
            new G4LogicalVolume(solidDet,
                det_mat, "Detector");
        new G4PVPlacement(0,
            G4ThreeVector(0, 0, 2.5 * cm),
            logicDet, "Detector",
            logicWorld,
            false,
            0,
            checkOverlaps);

        G4LogicalVolume* logicTar =
            new G4LogicalVolume(solidDet,
                det_mat, "Target");
        new G4PVPlacement(0,
            G4ThreeVector(0, 0, -2.5 * cm),
            logicTar, "Target",
            logicWorld,
            false,
            0,
            checkOverlaps);
        return physWorld;
    }
    void DetectorConstruction::ConstructSDandField()
    {
        G4String trackerChamberSDname = "SensitiveDetector";
        DetectorSD* aTrackerSD = new DetectorSD(trackerChamberSDname);
        G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
        SetSensitiveDetector("Detector", aTrackerSD, true);
    }
}