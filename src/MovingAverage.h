#pragma once

#include "ILowPassFilter.h"


namespace Moura {

class MovingAverage : public ILowPassFilter
{
private:
	int m_kernelSize;
	double m_sum;
	std::queue<double> m_buffer;

public:
	MovingAverage();

public:
	~MovingAverage();

public:
	MovingAverage& operator=(const MovingAverage& other); // Copy assignment
	MovingAverage& operator=(MovingAverage&& other);      // Move assignment

public:
	void SetParameter(const std::variant<int, double>& param) override;
	double FilterSignal(double input) override;
};

}
