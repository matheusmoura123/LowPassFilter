# LowPassFilter_task
LowPassFilter Class in C++

There are two types of low-pass filters implemented in the class:  
- (i) Moving average filter  
- (ii) 2nd order Butterworth filter

To use (i), initialize the class object with the type `LowPassFilter::FilterType::FIR`,  
then call `.SetKernel(int m)` to define the window size.

To use (ii), initialize the class object with the type `LowPassFilter::FilterType::IIR`,  
then call `.SetBWFreq(double fc)` to define the cut-off frequency (0 < fc < 0.5).

Then use `.FilterSignal(double input)` to get the filtered signal.

A `test.cpp` program is provided to test the filter. Inside `main`, a noisy signal is generated.  
The filtered signals using (i) and (ii) are saved in a `.csv` file, which can be opened in Excel for easy plotting and visualization.

To run `test.cpp`:

```bash
g++ test.cpp LowPassFilter.cpp -o test
./test
