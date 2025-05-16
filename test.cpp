#include "LowPassFilter.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {

    using namespace Moura;

    LowPassFilter lpf_fir(LowPassFilter::FilterType::FIR);
    lpf_fir.SetKernel(11);

    LowPassFilter lpf_bw(LowPassFilter::FilterType::IIR);
    lpf_bw.SetBWFreq(0.05);

    std::vector<double> filteredSignal_fir;
    std::vector<double> filteredSignal_bw;
    std::vector<double> signal;
    std::vector<double> time;

    std::srand(std::time(0));

    // INPUT SIGNAL + NOISE
    double signalFreq = 10;
    double signalAmplitude = 1.0;
    double noiseFreq = 80;
    double noiseAmplitude = 0.4; 
    double duration = 1.0;
    double samplingRate = 1000;

    double totalSamples = duration*samplingRate;

    for (int i = 0; i < totalSamples; ++i) {
        double r = -1 + 2*((double)rand()) / RAND_MAX;
        time.push_back(i/ samplingRate);
        signal.push_back(signalAmplitude*std::sin(signalFreq * 2 * g_pi * time[i]) + r*noiseAmplitude*std::sin(noiseFreq * 2 * g_pi * time[i]));
        filteredSignal_fir.push_back(lpf_fir.FilterSignal(signal[i]));
        filteredSignal_bw.push_back(lpf_bw.FilterSignal(signal[i]));
        // std::cout << time[i] << " " << signal[i] << " " << filteredSignal_fir[i] << " " << filteredSignal_bw[i] << std::endl;
    }

    std::ofstream file("signals.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 0;
    }
    for (size_t i = 0; i < totalSamples; ++i) {
        file << time[i] << "," << signal[i] << "," << filteredSignal_fir[i] << "," << filteredSignal_bw[i] << "\n";
    }
    file.close();

    return 0;
}
