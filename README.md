# LowPassFilter_task
C++ Implementation of Low-Pass Filters

This project implements two types of low-pass filters as derived classes from the `ILowPassFilter` interface:
- (i) Moving average filter  
- (ii) 2nd order Butterworth filter

Initialize the filter object as type `MovingAverage`. Use the method `.SetParameter(int windowSize)` to specify the window size (kernel size).

Initialize the filter object as type `Butterworth`. Use the method `.SetParameter(double cutoffFrequency)` to specify the cutoff frequency, which must satisfy: `0 < cutoffFrequency < 0.5`.

Call `.FilterSignal(double input)` on either filter object to obtain the filtered output for a given input sample.

`main.cpp` contains an example program that generates a noisy signal and applies both filters. The filtered outputs are saved to a `.csv` file, which can be opened in Excel or other tools for plotting and analysis.

Unit tests are provided in `test_LowPassFilter.cpp` using the Google Test framework to verify filter correctness and behavior.

This project uses CMake for building. To build the executable and tests:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
