#ifndef ENX01_SENSITIVE_DETECTOR_H
#define ENX01_SENSITIVE_DETECTOR_H

#include<G4VSensitiveDetector.hh>

using namespace std;

    class G4Step;
    class G4TouchableHistory;
    class DetectorSD : public G4VSensitiveDetector
    {
    private:
        static const int NOBINS = 1000;
        const double HIST_MAX;
        const double HIST_MIN;
        int histogram[NOBINS];
        int histogram_angle[NOBINS];
    public:
        ~DetectorSD();
        DetectorSD(G4String name);

        G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    };

#endif