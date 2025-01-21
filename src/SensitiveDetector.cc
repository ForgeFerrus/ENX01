
#include <fstream>
#include <iostream>
#include <memory> // Для розумних покажчиків
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <SensitiveDetector.hh>

using namespace std;

DetectorSD::DetectorSD(G4String name) 
:G4VSensitiveDetector(name), HIST_MAX(100 * MeV), HIST_MIN(0 * MeV)
{
    // Ініціалізація гістограм
    fill(begin(histogram), end(histogram), 0);
    fill(begin(histogram_angle), end(histogram_angle), 0);
    }
// Викликається на кожному кроці моделювання частинки, коли вона потрапляє в цей чутливий об'єм
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    G4cout.flush(); // Очищення буфера виводу
    G4cout << "ProcessHits called" << G4endl;
    // Отримання кінетичної енергії частинки з попереднього кроку, тобто початкової кінетичної енергії перед поточним кроком
    double energy = step->GetPreStepPoint()->GetKineticEnergy();
    // Визначення ширини біна (інтервалу) гістограми
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Перевірка, чи є частинка електроном
    if (step->GetTrack()->GetDefinition()->GetParticleName() == "e-") {
        // Визначення індексу (номеру) біна гістограми енергії
        int index = int(floor((energy - HIST_MIN) / bin_width));
        // Додавання +1 у відповідний бін
        if (index >= 0 && index < NOBINS)
            histogram[index]++;
        // Далі заповнення гістограми кутового розподілу
        // Отримання вектора напрямку частинки
        G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
        // Задаємо одиничний вектор у напрямку осі OZ
        G4ThreeVector* centerVector = new G4ThreeVector(0, 0, 1);
        // Застосування функції класу G4ThreeVector - знаходження кута відносно вектора centerVector
        double angle = ang.angle(*centerVector);
        // Визначення ширини біна в гістограмі кутового розподілу.
        // Оскільки вимірюються кути між векторами, максимальний кут дорівнює π (3.14), мінімальний 0
        double bin_width_ang = (3.14) / NOBINS;
        // Отримання номеру біна
        index = int(floor((angle) / bin_width_ang));
        // Заповнення гістограми
        if (index >= 0 && index < NOBINS)
            histogram_angle[index]++;
        // Виведення інформації про хіт у термінал 
        G4cout << "Energy: " << energy / MeV << " MeV, Angle: " << angle << " radians" << G4endl;
    }
    // Оскільки ми хочемо тільки виміряти параметри частинок після проходження мішені і не цікавимося подальшою їх долею в детекторі, то їх знищуємо - встановлюємо статус зупинено і знищено (fStopAndKill)
    step->GetTrack()->SetTrackStatus(fStopAndKill);
    return true;
}
DetectorSD::~DetectorSD()
{
    G4cout << "Destructor called" << G4endl;
    // Запис гістограми енергії у файл "spectrum.dat"
    std::ofstream file("spectrum.dat");
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    for (int i = 0; i < NOBINS; i++) {
        double energy = i * bin_width + HIST_MIN;
        file << std::setw(15) << energy / MeV << " " << std::setw(15) << histogram[i] << std::endl;
    }
    file.close();
    // Запис гістограми кутів у файл "angle.dat"
    file.open("angle.dat");
    bin_width = (3.14) / NOBINS;
    for (int i = 0; i < NOBINS; i++) {
        double angle = i * bin_width;
        file << std::setw(15) << angle << " " << std::setw(15) << histogram_angle[i] << std::endl;
    }
    file.close();
}
