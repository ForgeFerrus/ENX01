#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include<G4SystemOfUnits.hh>
#include<G4ThreeVector.hh>
#include<SensitiveDetector.hh>

using namespace std;

DetectorSD::DetectorSD(G4String name):G4VSensitiveDetector(name),
            HIST_MAX(100 * MeV),
            HIST_MIN(0 * MeV)
    {
        for (int i = 0; i < NOBINS; i++) {
            histogram[i] = 0;
            histogram_angle[i] = 0;
        }
    }
    //Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
    G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
    {
        G4cout << "ProcessHits called" << G4endl;
        // Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
        // кинетическую энегрию перед текущим шагом
        double energy = step->GetPreStepPoint()->GetKineticEnergy();
        // Вычисляем ширину бина (интерва) гистограммы
        double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
            if (step->GetTrack()->GetDefinition()->GetParticleName() == "e-") {
            // Определяем индекс (номер) бина гистограммы энергии
            int index = int(floor((energy - HIST_MIN) / bin_width));
            // Добавляем +1 в соответствующий бин
            if (index >= 0 && index < NOBINS)
                histogram[index]++;
            // Далее заполняем гистограмму углового распределения
            // Получаем вектор направления частицы
    G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
            // Задаем единичный вектор в направлении оси OZ
    G4ThreeVector* centerVector = new G4ThreeVector(0, 0, 1);
            // Применяем фунцию класса G4ThreeVector - находим угол относительно
            // вектора centerVector
          double angle = ang.angle(*centerVector);
            // Определяем ширину бина в гистограмме углового распределения.
            // Так как у нас измеряются углы между векторами, то максимальный
            // угол равен пи 3.14, минимальный 0
          double bin_width_ang = (3.14) / NOBINS;
            // Получаем номер бина
            index = int(floor((angle) / bin_width_ang));
            // Заполняем гистограмму
            if (index >= 0 && index < NOBINS)
                histogram_angle[index]++;
            // Вивести інформацію про хіт у термінал 
        G4cout << "Energy: " << energy / MeV << " MeV, Angle: " << angle << " radians" << G4endl; }
        // Так как мы хотим только измерить параметры частиц после прохождения
        // мишени и не интересуемся дальнейшей их судьбой в детекторе, то их убиваем -
        // устанавливаем статус остановлено и уничтожено (fStopAndKill)
            step->GetTrack()->SetTrackStatus(fStopAndKill);
            return true;
        }
    DetectorSD::~DetectorSD()
    {
        G4cout << "Destructor called" << G4endl;
        std::ofstream file("spectrum.dat");
        double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
        for (int i = 0; i < NOBINS; i++)
        {
            double energy = i * bin_width + HIST_MIN;
            file << std::setw(15) << energy / MeV << " "
                << std::setw(15) << histogram[i] << std::endl;
        }
        file.close();
        file.open("angle.dat");
        bin_width = (3.14) / NOBINS;
        for (int i = 0; i < NOBINS; i++)
        {
            double angle = i * bin_width;
            file << std::setw(15) << angle << " "
                << std::setw(15) << histogram_angle[i] << std::endl;
        }
        file.close();
    }