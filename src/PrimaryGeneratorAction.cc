#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include <PrimaryGeneratorAction.hh>

namespace ENX01
{
    PrimaryGeneratorAction::PrimaryGeneratorAction() {
    // Налаштування генератора частинок
    G4int nParticles = 1;
        fParticleGun = new G4ParticleGun(nParticles);
    // Визначення властивостей частинки
    const G4String& particleName = "e-";
    // Пошук частинки (e-) в таблиці частинок G4Particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle
       = particleTable->FindParticle(particleName);
    // Встановлення типу частинки для генератора частинок
        fParticleGun->SetParticleDefinition(particle);
    // Встановлення напрямку руху частинки
    G4ThreeVector momentumDirection = G4ThreeVector(0, 0, 1);
        fParticleGun->SetParticleMomentumDirection(momentumDirection);
    // Встановлення енергії частинки
    G4double energy = 1.0 * MeV; // Визначення значення енергії
        fParticleGun->SetParticleEnergy(energy);
    }
    PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    // Очищення пам'яті, видалення об'єкта fParticleGun
        delete fParticleGun;
    }
    void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
    {
    // Випадковий вибір початкових координат x та y у межах діаметра 1 мм
    G4double radius = .5 * mm;
    // Генерація випадкових координат x та y у межах цього радіуса
    // Щоб уникнути використання повільних методів, таких як sin та cos,
    // ми генеруємо випадкові значення у квадраті та відкидаємо ті, що
    // знаходяться за межами кола
        double x, y;
            do {
                x = G4UniformRand() * (1.0 * radius) - radius;
                y = G4UniformRand() * (1.0 * radius) - radius;
        }   while (x * x + y * y > radius * radius);
	// Встановлення позиції частинки
    G4ThreeVector position = G4ThreeVector(x, y, -2.5 * cm);
        fParticleGun->SetParticlePosition(position);
        fParticleGun->GeneratePrimaryVertex(event);
    } // Генерація первинних частинок
}
