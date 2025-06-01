#pragma once

#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <variant>
#include <stdexcept>

namespace Moura {

const double g_pi = 3.14159265358979323846;

class ILowPassFilter
{
public:
	~ILowPassFilter() = default;

public:
	virtual void SetParameter(const std::variant<int, double>& param) = 0;
	virtual double FilterSignal(double input) = 0;
};
}
