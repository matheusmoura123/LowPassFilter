// #include "stdafx.h"
#include "MovingAverage.h"

namespace Moura {

MovingAverage::MovingAverage()
	: m_kernelSize(51)
	, m_sum(0.0)
	, m_buffer()
{}

MovingAverage::~MovingAverage()
{}

MovingAverage& MovingAverage::operator=(const MovingAverage& other)
{
	this->m_kernelSize = other.m_kernelSize;
	this->m_sum = other.m_sum;
	this->m_buffer = other.m_buffer;
	return *this;
}

MovingAverage& MovingAverage::operator=(MovingAverage&& other)
{
	std::swap(this->m_kernelSize, other.m_kernelSize);
	std::swap(this->m_sum, other.m_sum);
	std::swap(this->m_buffer, other.m_buffer);
	return *this;
}

void MovingAverage::SetParameter(const std::variant<int, double>& param)
{	
	if (const int* pVal = std::get_if<int>(&param)) {
		int m =  *pVal;
		if (m > 0) {
			m_kernelSize = (m % 2) ? m : m+1;
			return;
		}
	}
	std::cerr << "Error: Kernel size should be integer bigger than 0\n";	
}

double MovingAverage::FilterSignal(double input)
{	
	double output = 0.0;
	m_buffer.push(input);
	m_sum += input;
	if (m_buffer.size() > m_kernelSize)
	{
		m_sum -= m_buffer.front();
		m_buffer.pop();
	}
	output = m_sum/m_kernelSize;
	return output;
}

}
