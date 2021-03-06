#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"
#include <time.h>

class CParticleEmitter
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CParticleEmitter();

	// @param dt - ������� �� ������� � ���������� ������� Advance.
	std::shared_ptr<CStaticParticle>	Emit();

	void								SetPlaceSize(const glm::vec2 &value);
	glm::vec2							GetPlaceSize() const;

	void								SetPosition(const glm::vec2 &value);
	glm::vec2							GetPosition() const;

	void								SetEmitIntervalRange(float minValue, float maxValue);
	void								SetAngleRange(float minValue, float maxValue);

	void								SetXPositionRange(float xMin, float xMax);
	void								SetYPositionRange(float yMin, float yMax);

	void								SetAmplitude(float min, float max);
	void								SetFrequency(float min, float max);
	//////////////////////////////////////////////////////////////////////
	// Using
private:
	using linear_random_float = std::uniform_real_distribution<float>;
	using normal_random_float = CClampedNormalDistribution;
	using linear_random_int = std::uniform_int_distribution<int>;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	glm::vec2							m_position;
	glm::vec2							m_placeSize;

	normal_random_float					m_xRange;
	normal_random_float					m_yRange;

	normal_random_float					m_emitIntervalRange;
	normal_random_float					m_angleRange;

	normal_random_float					m_amplitude;
	normal_random_float					m_frequency;


	std::mt19937						m_random;
	//////////////////////////////////////////////////////////////////////
};
