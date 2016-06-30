#pragma once

#include "DynamicParticle.h"
#include "NormalDistribution.h"

class CParticleEmitter
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CParticleEmitter();

	// @param dt - разница во времени с предыдущим вызовом Advance.
	void								Advance(float dt);
	bool								IsEmitReady()const;
	std::unique_ptr<CDynamicParticle>	Emit();

	void								SetPosition(const glm::vec2 &value);

	void								SetLifetimeRange(float minValue, float maxValue);
	void								SetRadiusRange(float minValue, float maxValue);

	void								SetEmitIntervalRange(float minValue, float maxValue);
	void								SetSpeedRange(float minValue, float maxValue);
	void								SetAngleRange(float minValue, float maxValue);
	//////////////////////////////////////////////////////////////////////
	// Using
private:
	using linear_random_float = std::uniform_real_distribution<float>;
	using normal_random_float = CClampedNormalDistribution;
	using linear_random_int = std::uniform_int_distribution<int>;
	//////////////////////////////////////////////////////////////////////
	// Data
private:

	float								m_elapsedSeconds = 0;
	float								m_nextEmitTime = 0;
	glm::vec2							m_position;

	normal_random_float					m_lifetimeRange;
	linear_random_float					m_radiusRange;

	normal_random_float					m_emitIntervalRange;
	normal_random_float					m_speedRange;
	normal_random_float					m_angleRange;

	std::mt19937						m_random;
	//////////////////////////////////////////////////////////////////////
};
