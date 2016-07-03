#include "stdafx.h"
#include "ParticleEmitter.h"

CParticleEmitter::CParticleEmitter()
{
	std::random_device rd;
	m_random.seed(rd());

	srand(time(nullptr));
}


std::unique_ptr<CDynamicParticle> CParticleEmitter::Emit()
{
	auto pParticle = std::make_unique<CDynamicParticle>();

	const float angle = m_angleRange(m_random);

	bool sign = bool(rand() % 2);
	pParticle->SetNegativeCharge(sign);


	float x = m_xRange(m_random);
	float y = m_yRange(m_random);
	pParticle->SetOrigin(m_position);
	pParticle->SetPosition(x, y);

	return pParticle;
}

void CParticleEmitter::SetPlaceSize(const glm::vec2 & value)
{
	m_placeSize = value;

	SetXPositionRange(0.f, m_placeSize.x);
	SetYPositionRange(0.f, m_placeSize.y);

}

glm::vec2 CParticleEmitter::GetPlaceSize() const
{
	return m_placeSize;
}

void CParticleEmitter::SetPosition(const glm::vec2 &value)
{
	m_position = value;
}

glm::vec2 CParticleEmitter::GetPosition() const
{
	return m_position;
}

void CParticleEmitter::SetEmitIntervalRange(float minValue, float maxValue)
{
	m_emitIntervalRange.param(minValue, maxValue);
}

void CParticleEmitter::SetAngleRange(float minValue, float maxValue)
{
	m_angleRange.param(minValue, maxValue);
}

void CParticleEmitter::SetXPositionRange(float xMin, float xMax)
{
	m_xRange.param(xMin, xMax);
}

void CParticleEmitter::SetYPositionRange(float yMin, float yMax)
{
	m_yRange.param(yMin, yMax);
}
