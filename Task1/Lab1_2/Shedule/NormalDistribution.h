#pragma once

#include <vector>
#include <memory>
#include <random>


// ������� �� ������ http://stackoverflow.com/questions/28618900
class CClampedNormalDistribution
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// m_distribution ������� ��� ���������:
	// `mean`, �.�. ��������� �������� � ������������ ���. ��������
	// `stddev`, �.�. ����������� ���������� (���������)
	// �� ������� ��� ��������� �� min/max.
	void param(float min, float max)
	{
		using param_type = std::normal_distribution<float>::param_type;
		const float mean = (min + max) / 2.f;
		const float stddev = (max - min) / 6.f;
		m_distribution.param(param_type(mean, stddev));
		m_min = min;
		m_max = max;
	}

	// ���������� ������������� ����� �������� �� ��� ��������� float
	// �� �� ����� ��������, ���������� �� ��������� [min, max]
	// �������������, ����� ��������� ����� 0.3% ��������.
	float operator ()(std::mt19937 &random) {
		while (true) {
			float number = m_distribution(random);
			if (number >= m_min && number <= m_max)
				return number;
		}
	}
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::normal_distribution<float> m_distribution;
	float m_min = 0.f;
	float m_max = 0.f;
	//////////////////////////////////////////////////////////////////////
};
