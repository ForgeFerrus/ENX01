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
    // ������������ ���������� ��������
    G4int nParticles = 1;
        fParticleGun = new G4ParticleGun(nParticles);
    // ���������� ������������ ��������
    const G4String& particleName = "e-";
    // ����� �������� (e-) � ������� �������� G4Particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle
       = particleTable->FindParticle(particleName);
    // ������������ ���� �������� ��� ���������� ��������
        fParticleGun->SetParticleDefinition(particle);
    // ������������ �������� ���� ��������
    G4ThreeVector momentumDirection = G4ThreeVector(0, 0, 1);
        fParticleGun->SetParticleMomentumDirection(momentumDirection);
    // ������������ ����㳿 ��������
    G4double energy = 1.0 * MeV; // ���������� �������� ����㳿
        fParticleGun->SetParticleEnergy(energy);
    }
    PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    // �������� ���'��, ��������� ��'���� fParticleGun
        delete fParticleGun;
    }
    void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
    {
    // ���������� ���� ���������� ��������� x �� y � ����� ������� 1 ��
    G4double radius = .5 * mm;
    // ��������� ���������� ��������� x �� y � ����� ����� ������
    // ��� �������� ������������ �������� ������, ����� �� sin �� cos,
    // �� �������� �������� �������� � ������� �� �������� �, ��
    // ����������� �� ������ ����
        double x, y;
            do {
                x = G4UniformRand() * (1.0 * radius) - radius;
                y = G4UniformRand() * (1.0 * radius) - radius;
        }   while (x * x + y * y > radius * radius);
	// ������������ ������� ��������
    G4ThreeVector position = G4ThreeVector(x, y, -2.5 * cm);
        fParticleGun->SetParticlePosition(position);
        fParticleGun->GeneratePrimaryVertex(event);
    } // ��������� ��������� ��������
}
