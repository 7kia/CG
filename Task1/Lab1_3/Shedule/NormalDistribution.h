#pragma once

#include <vector>
#include <memory>
#include <random>


// —оздано на основе http://stackoverflow.com/questions/28618900
class CClampedNormalDistribution
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// m_distribution требует два параметра:
	// `mean`, т.е. медианное значение и одновременно мат. ожидание
	// `stddev`, т.е. стандартное отклонение (дисперсию)
	// мы выводим эти параметры из min/max.
	void param(float min, float max)
	{
		using param_type = std::normal_distribution<float>::param_type;
		const float mean = (min + max) / 2.f;
		const float stddev = (max - min) / 6.f;
		m_distribution.param(param_type(mean, stddev));
		m_min = min;
		m_max = max;
	}

	// Ќормальное распределение выдаЄт значени€ на всЄм диапазоне float
	// Ќо мы режем значени€, выпадающие из диапазона [min, max]
	// —татистически, будет выброшено около 0.3% значений.
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
