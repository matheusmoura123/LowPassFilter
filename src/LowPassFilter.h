#pragma once

#include <vector>
#include <queue>
#include <cmath>
#include <iostream>

namespace Moura {

const double g_pi = 3.14159265358979323846;

class LowPassFilter
{
	// ------------------------------------------------------------------------
	// Typedefs
	//
public:


	// ------------------------------------------------------------------------
	// Enums
	//
public:
	enum FilterType
	{
		FIR,
		IIR
	};

	// ------------------------------------------------------------------------
	// Structs
	//
public:

	// ------------------------------------------------------------------------
	// Classes
	//

	// ------------------------------------------------------------------------
	// Variables
	//
public:


private:
	FilterType m_filterType;
	int m_kernelSize;
	double m_firSum;
	std::queue<double> m_firBuffer;
	double m_bwCutoffFreq; 
	std::vector<double> m_bwCoef;
	std::vector<double> m_bwMemory;

	// ------------------------------------------------------------------------
	// Constructors
	//
public:
	LowPassFilter();
	LowPassFilter(FilterType type);

	// ------------------------------------------------------------------------
	// Destructor
	//
public:
	~LowPassFilter();

	// ------------------------------------------------------------------------
	// Operators
	//
public:
	LowPassFilter& operator=(const LowPassFilter& other); // Copy assignment
	LowPassFilter& operator=(LowPassFilter&& other);      // Move assignment

	// ------------------------------------------------------------------------
	// Methods
	//
public:
	void SetKernel(int m);
	void SetBWFreq(double fc);
	double FilterSignal(double input);


private:
	void ComputeBWCoef();
};

}
