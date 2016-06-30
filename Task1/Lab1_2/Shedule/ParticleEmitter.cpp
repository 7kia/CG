#include "stdafx.h"
#include "ParticleEmitter.h"

CParticleEmitter::CParticleEmitter()
{
	std::random_device rd;
	m_random.seed(rd());
}

void CParticleEmitter::Advance(float dt)
{
	m_elapsedSeconds += dt;
}

bool CParticleEmitter::IsEmitReady() const
{
	return m_elapsedSeconds > m_nextEmitTime;
}

std::unique_ptr<CDynamicParticle> CParticleEmitter::Emit()
{
	auto pParticle = std::make_unique<CDynamicParticle>();

	// ќпредел€ем врем€ по€влени€ следующей частицы.
	m_elapsedSeconds -= m_nextEmitTime;
	m_nextEmitTime = m_emitIntervalRange(m_random);

	const float speed = m_speedRange(m_random);
	const float angle = m_angleRange(m_random);

	const glm::vec2 velocity = { speed * sinf(angle), speed * cosf(angle) };

	pParticle->SetLifetime(m_lifetimeRange(m_random));
	pParticle->SetVelocity(velocity);
	pParticle->SetOrigin(m_position);

	return pParticle;
}

void CParticleEmitter::SetPosition(const glm::vec2 &value)
{
	m_position = value;
}

void CParticleEmitter::SetLifetimeRange(float minValue, float maxValue)
{
	m_lifetimeRange.param(minValue, maxValue);
}

void CParticleEmitter::SetRadiusRange(float minValue, float maxValue)
{
	m_radiusRange.param(linear_random_float::param_type(minValue, maxValue));
}

void CParticleEmitter::SetEmitIntervalRange(float minValue, float maxValue)
{
	m_emitIntervalRange.param(minValue, maxValue);
}

void CParticleEmitter::SetSpeedRange(float minValue, float maxValue)
{
	m_speedRange.param(minValue, maxValue);
}

void CParticleEmitter::SetAngleRange(float minValue, float maxValue)
{
	m_angleRange.param(minValue, maxValue);
}
