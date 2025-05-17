// #include "stdafx.h"
#include "LowPassFilter.h"



namespace Moura {

LowPassFilter::LowPassFilter()
	: m_filterType(FIR) 
	, m_kernelSize(51)
	, m_firSum(0.0)
	, m_firBuffer()
	, m_bwCutoffFreq(0.05)
	, m_bwCoef(5)
	, m_bwMemory(5)
{}

LowPassFilter::LowPassFilter(FilterType type)
	: m_filterType(type)
	, m_kernelSize(51)
	, m_firSum(0.0)
	, m_firBuffer()
	, m_bwCutoffFreq(0.05)
	, m_bwCoef(5)
	, m_bwMemory(5)
{
	if (m_filterType == IIR) {ComputeBWCoef();}
}

LowPassFilter::~LowPassFilter()
{}

LowPassFilter& LowPassFilter::operator=(const LowPassFilter& other)
{
	this->m_filterType = other.m_filterType;
	this->m_kernelSize = other.m_kernelSize;
	this->m_firSum = other.m_firSum;
	this->m_firBuffer = other.m_firBuffer;
	this->m_bwCutoffFreq = other.m_bwCutoffFreq;
	this->m_bwCoef = other.m_bwCoef;
	this->m_bwMemory = other.m_bwMemory;
	return *this;
}

LowPassFilter& LowPassFilter::operator=(LowPassFilter&& other)
{
	std::swap(this->m_filterType, other.m_filterType);
	std::swap(this->m_kernelSize, other.m_kernelSize);
	std::swap(this->m_firSum, other.m_firSum);
	std::swap(this->m_firBuffer, other.m_firBuffer);
	std::swap(this->m_bwCutoffFreq, other.m_bwCutoffFreq);
	std::swap(this->m_bwCoef, other.m_bwCoef);
	std::swap(this->m_bwMemory, other.m_bwMemory);
	return *this;
}

void LowPassFilter::SetKernel(int m)
{ 
	m_kernelSize = (m % 2) ? m : m+1;
}

void LowPassFilter::SetBWFreq(double fc)
{	
	if (fc <= 0.0 || fc >= 0.5) {
		std::cerr << "Error: Cut-off Frequency should be 0 < fc < 0.5\n";
		return;
	}
	m_bwCutoffFreq = fc;
	ComputeBWCoef();
}

double LowPassFilter::FilterSignal(double input)
{	
	double output = 0.0;
	if (m_filterType == FIR)
	{
		m_firBuffer.push(input);
		m_firSum += input;
		if (m_firBuffer.size() > m_kernelSize)
		{
			m_firSum -= m_firBuffer.front();
			m_firBuffer.pop();
		}
		output = m_firSum/m_kernelSize;
	}

	if (m_filterType == IIR)
	{
		m_bwMemory[0] = input;
		for (int i = 0; i < 5; ++i)
		{
			output += m_bwCoef[i]*m_bwMemory[i];
		}
		m_bwMemory[4] = m_bwMemory[3];
		m_bwMemory[3] = output;
		m_bwMemory[2] = m_bwMemory[1];
		m_bwMemory[1] = m_bwMemory[0];
	}
	
	return output;

}

void LowPassFilter::ComputeBWCoef()
{
	double wc = 2*g_pi*m_bwCutoffFreq;
	double wac= std::tan(wc/2);
	double norm = std::pow(wac,2) + sqrt(2.0)*wac + 1;

	double b0 = std::pow(wac, 2) / norm;
	double b1 = 2*b0;
	double b2 = b0;
	double a1 = - (2*std::pow(wac,2) - 2) / norm;
	double a2 = - (std::pow(wac,2) - sqrt(2.0)*wac + 1) / norm;

	m_bwCoef = {b0, b1, b2, a1, a2};
	// std::cout << m_bwCoef[0] << " " << m_bwCoef[1] << " " << m_bwCoef[2] << " " << m_bwCoef[3] << " " << m_bwCoef[4] << std::endl;
}


}
