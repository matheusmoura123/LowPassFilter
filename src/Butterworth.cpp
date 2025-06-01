// #include "stdafx.h"
#include "Butterworth.h"

namespace Moura {

Butterworth::Butterworth()
	: m_cutOffFreq(0.05)
	, m_coef(5)
	, m_memory(5)
{
	ComputeCoef();
}

Butterworth::~Butterworth()
{}

Butterworth& Butterworth::operator=(const Butterworth& other)
{
	this->m_cutOffFreq = other.m_cutOffFreq;
	this->m_coef = other.m_coef;
	this->m_memory = other.m_memory;
	return *this;
}

Butterworth& Butterworth::operator=(Butterworth&& other)
{
	std::swap(this->m_cutOffFreq, other.m_cutOffFreq);
	std::swap(this->m_coef, other.m_coef);
	std::swap(this->m_memory, other.m_memory);
	return *this;
}

void Butterworth::SetParameter(const std::variant<int, double>& param)
{	
	if (const double* pVal = std::get_if<double>(&param)) {
		double fc =  *pVal;
		if (fc > 0.0 && fc < 0.5) {
			m_cutOffFreq = fc;
			ComputeCoef();
			return;
		}
	}
	throw std::invalid_argument("Cut-off Frequency should be 0 < fc < 0.5");
}

double Butterworth::FilterSignal(double input)
{	
	double output = 0.0;
	m_memory[0] = input;
	for (int i = 0; i < 5; ++i)
	{
		output += m_coef[i]*m_memory[i];
	}
	m_memory[4] = m_memory[3];
	m_memory[3] = output;
	m_memory[2] = m_memory[1];
	m_memory[1] = m_memory[0];
	return output;

}

void Butterworth::ComputeCoef()
{
	double wc = 2*g_pi*m_cutOffFreq;
	double wac= std::tan(wc/2);
	double norm = std::pow(wac,2) + sqrt(2.0)*wac + 1;

	double b0 = std::pow(wac, 2) / norm;
	double b1 = 2*b0;
	double b2 = b0;
	double a1 = - (2*std::pow(wac,2) - 2) / norm;
	double a2 = - (std::pow(wac,2) - sqrt(2.0)*wac + 1) / norm;

	m_coef = {b0, b1, b2, a1, a2};
	// std::cout << m_coef[0] << " " << m_coef[1] << " " << m_coef[2] << " " << m_coef[3] << " " << m_coef[4] << std::endl;
}

}
