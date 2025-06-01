#include "LowPassFilter.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace Moura;

int main() {


    LowPassFilter lpf_fir(LowPassFilter::FIR);
    lpf_fir.SetKernel(41);

    LowPassFilter lpf_bw(LowPassFilter::IIR);
    lpf_bw.SetBWFreq(0.02);

    LowPassFilter lpf_bw_2(LowPassFilter::IIR);
    lpf_bw_2.SetBWFreq(0.02);

    std::vector<double> filteredSignal_fir;
    std::vector<double> filteredSignal_bw;
    std::vector<double> signal;
    std::vector<double> time;

    std::srand(static_cast<unsigned int>(std::time(0)));

    // INPUT SIGNAL + NOISE
    double signalFreq = 10;
    double signalAmplitude = 1.0;
    double noiseFreq = 200;
    double noiseAmplitude = 0.4; 
    double duration = 1.0;
    double samplingRate = 1000;

    double totalSamples = duration*samplingRate;

    for (int i = 0; i < totalSamples; ++i) {
        double r = -1 + 2*((double)rand()) / RAND_MAX;
        time.push_back(i/ samplingRate);

        double sig;
        // Sine Signal
        // sig = signalAmplitude*std::sin(signalFreq * 2 * g_pi * time[i]);

        // Step Signal
        sig = (i>totalSamples/3 && i<totalSamples/2) ? signalAmplitude : 0;

        signal.push_back(sig + r*noiseAmplitude*std::sin(noiseFreq * 2 * g_pi * time[i]));

        filteredSignal_fir.push_back(lpf_fir.FilterSignal(signal[i]));
        filteredSignal_bw.push_back(lpf_bw_2.FilterSignal(lpf_bw.FilterSignal(signal[i])));
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
