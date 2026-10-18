#include <iostream>
#include <iomanip>

struct _capacitor {
    double *time;   // time array
    double *voltage; // voltage array
    double *current; // current array
    double C;       // capacitance value
};
typedef struct _capacitor Capacitor;

// Constants
const double DT = 1e-10l; // timestep (s)
const int NSTEPS = 50000; // final time/DT = 5e-6/1e-10
const double R = 1e3; // resistance (ohms)
const double CAP = 100e-12; // capacitance (F)
const double I_CONST = 1e-2; // const. current source (A)
const double V0 = 10.0; // const. voltage source (V)
const int PRINT_INT = 200; // to print every 200 timesteps

// Dynamically allocate arrays
void allocateCapacitor(Capacitor *cap, int nsteps, double C) {
    cap->C = C;
    cap->time = new double[nsteps + 1];
    cap->voltage = new double[nsteps + 1];
    cap->current = new double[nsteps + 1];
}

// Free arrays and reset ptrs
void freeCapacitor(Capacitor *cap) {
    delete[] cap->time;
    delete[] cap->voltage;
    delete[] cap->current;
    cap->time = cap->voltage = cap->current = nullptr;
}

// Constant current supply
void solveConstantCurrent(Capacitor *cap, int nsteps, double dt, double I) {
    // Initial conditions (timestep 0)
    cap->time[0] = 0.0;
    cap->voltage[0] = 0.0;
    cap->current[0] = I;

    for (int t = 1; t <= nsteps; t++) {
        cap->time[t] = t * dt;
        cap->current[t] = I; // source holds current constant
        cap->voltage[t] = cap->voltage[t - 1] + cap->current[t - 1] * dt / cap->C;
    }
}

// Constant voltage supply with series resistor
void solveConstantVoltage(Capacitor *cap, int nsteps, double dt, double R, double V0) {
    // Initial conditions (timestep 0)
    cap->time[0] = 0.0;
    cap->voltage[0] = 0.0;
    cap->current[0] = V0 / R;

    for (int t = 1; t <= nsteps; t++) {
        cap->time[t] = t * dt;
        cap->current[t] = cap->current[t - 1] - cap->current[t - 1] * dt / (R * cap->C);
        cap->voltage[t] = cap->voltage[t - 1] + cap->current[t - 1] * dt / cap->C;
    }
}

// Print results every interval timesteps
void printResults(const Capacitor *cap, int nsteps, int interval, const char *title) {
    std::cout << "\n" << title << "\n";
    std::cout << std::setw(6) << "step" // setting widths with an extra padding
              << std::setw(16) << "time (s)"
              << std::setw(16) << "voltage (V)"
              << std::setw(16) << "current (A)" << "\n";

    std::cout << std::scientific << std::setprecision(6); // scientific notation
    for (int t = 0; t <= nsteps; t += interval) {
        std::cout << std::setw(6) << t
                  << std::setw(16) << cap->time[t]
                  << std::setw(16) << cap->voltage[t]
                  << std::setw(16) << cap->current[t] << "\n";
    }
}

int main(void) {
    Capacitor cc; // const. current case
    Capacitor cv; // const. voltage case

    allocateCapacitor(&cc, NSTEPS, CAP);
    allocateCapacitor(&cv, NSTEPS, CAP);

    solveConstantCurrent(&cc, NSTEPS, DT, I_CONST);
    solveConstantVoltage(&cv, NSTEPS, DT, R, V0);

    printResults(&cc, NSTEPS, PRINT_INT, "Constant current source (I = 1e-2 A)");
    printResults(&cv, NSTEPS, PRINT_INT, "Constant voltage source (V0 = 10 V, R = 1 kOhm)");

    freeCapacitor(&cc);
    freeCapacitor(&cv);
    return 0;
}
