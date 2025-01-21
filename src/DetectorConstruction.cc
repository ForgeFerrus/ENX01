#include <SensitiveDetector.hh>
#include <DetectorConstruction.hh>

#include <locale>
#include <iostream>
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"

namespace ENX01 {

    int main() {
        // Вивід тексту
        std::wcout << L"Hello, world!" << std::endl;
        return 0;
    }
    // Функція для читання розмірів з консолі
    void ReadWorldDimensions(G4double& world_sizeXY, G4double& world_sizeZ) {
        std::cout << "vvedit rosmir world XY: ";
        double sizeXY;
        std::cin >> sizeXY;
        world_sizeXY = sizeXY * cm;

        std::cout << "vvedit rosmir world Z: ";
        double sizeZ;
        std::cin >> sizeZ;
        world_sizeZ = sizeZ * cm;
    }
    // Функція для читання розмірів детектора з консолі
    void ReadDetectorDimensions(G4double& det_sizeXY, G4double& det_sizeZ) {
        std::cout << "vvedit rosmir detector XY: ";
        double sizeXY;
        std::cin >> sizeXY;
        det_sizeXY = sizeXY * cm;

        std::cout << "vvedit rosmir detector Z: ";
        double sizeZ;
        std::cin >> sizeZ;
        det_sizeZ = sizeZ * cm;
    }
    // Будуємо тут наші детектори
    G4VPhysicalVolume* DetectorConstruction::Construct()
    {
        // Менеджер матеріалів nist
        G4NistManager* nist = G4NistManager::Instance();
        // Почнемо з побудови світу:
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
        G4bool checkOverlaps = true;
        // Значення за замовчуванням для світу
        G4double world_sizeXY = 30 * cm;
        G4double world_sizeZ = 20 * cm;
        // Читання розмірів світу з консолі 
        ReadWorldDimensions(world_sizeXY, world_sizeZ);
        auto solidWorld = new G4Box("World", world_sizeXY / 2, world_sizeXY / 2, world_sizeZ / 2);
		auto logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
        
        G4VPhysicalVolume* physWorld = new G4PVPlacement(0,
            G4ThreeVector(),
            logicWorld,
            "World",
            0,
            false,
            0,
            checkOverlaps);
        // Створюємо вольфрамову мішень
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
        // Цільове положення та обертання
        G4ThreeVector targetPos = G4ThreeVector(); // 0,0
        G4RotationMatrix* targetRotation = new G4RotationMatrix();
        // Розмістити ціль у світі
        new G4PVPlacement(targetRotation,
            targetPos,
            logicTarget,
            "Target",
            logicWorld,
            false,
            0);
        fBremsVolume = logicTarget;

        // Значення за замовчуванням для детектора
        G4double det_sizeXY = 10 * cm;
        G4double det_sizeZ = 5 * cm;

        // Читання розмірів детектора з консолі
        ReadDetectorDimensions(det_sizeXY, det_sizeZ);

        G4Box* solidDet = new G4Box("Detector",
            0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ);
        // Розміщення детектора
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
        // Повернення фізичного об'єму світу
        return physWorld;
    }
    // Конструкція сенсорного детектора та поля
    void DetectorConstruction::ConstructSDandField()
	{ // Створюємо сенсорний детектор
        G4String trackerChamberSDname = "SensitiveDetector";
        DetectorSD* aTrackerSD = new DetectorSD(trackerChamberSDname);
        G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
        SetSensitiveDetector("Detector", aTrackerSD, true);
    } // Ця функція визначає сенсорний детектор та його поле
    G4VPhysicalVolume* DetectorConstruction::Construct(int argc, char** argv)
    { //функція є заглушкою та не виконує жодних дій. Вона завжди повертає nullptr.
        return nullptr;
    } // 
} // закриває простір імені
