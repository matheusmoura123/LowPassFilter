#pragma once

#include "ILowPassFilter.h"

namespace Moura {

class Butterworth : public ILowPassFilter
{
private:
	double m_cutOffFreq; 
	std::vector<double> m_coef;
	std::vector<double> m_memory;

public:
	Butterworth();

public:
	~Butterworth();

public:
	Butterworth& operator=(const Butterworth& other); // Copy assignment
	Butterworth& operator=(Butterworth&& other);      // Move assignment

public:
	void SetParameter(const std::variant<int, double>& param) override;
	double FilterSignal(double input) override;

private:
	void ComputeCoef();
};

}
