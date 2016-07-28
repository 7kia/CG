#include "stdafx.h"
#include "ParticleEmitter.h"

CParticleEmitter::CParticleEmitter()
{
	std::random_device rd;
	m_random.seed(rd());

	srand(unsigned(time(nullptr)));
}

std::shared_ptr<CStaticParticle> CParticleEmitter::Emit()
{
	std::shared_ptr<CStaticParticle> pParticle;

	float x = m_xRange(m_random);
	float y = m_yRange(m_random);

	bool sign = bool(rand() % 2);

	if ((rand() % 2) == 1)
	{
		pParticle = std::make_shared<CDynamicParticle>();

		pParticle->SetSign(sign);

		pParticle->SetOrigin(m_position);
		pParticle->SetPosition(x, y);

	}
	else
	{
		pParticle = std::make_shared<CStaticParticle>();

		float amplitude = m_amplitude(m_random);
		float frequency = m_frequency(m_random);


		MoveFunction sinus = [&](float dt, glm::vec2 position)
		{
			position.x += dt * 75.f;
			position.y = sin((position.x - WINDOW_WIDTH / 2.f - x) * 100.f/*frequency*/) * 45.f/*amplitude*/ + WINDOW_HEIGTH / 2.f + y;

			return position;
		};

		pParticle->SetMoveFunction(std::make_shared<MoveFunction>(sinus));
		pParticle->SetSign(sign);

		pParticle->SetOrigin(m_position);
		pParticle->SetPosition(x, y);

		
	}

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

void CParticleEmitter::SetAmplitude(float min, float max)
{
	m_amplitude.param(min, max);
}

void CParticleEmitter::SetFrequency(float min, float max)
{
	m_frequency.param(min, max);
}
