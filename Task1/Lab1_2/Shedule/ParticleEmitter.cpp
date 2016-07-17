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

		std::function<glm::vec2(float, glm::vec2)> sinus = [&](float dt, glm::vec2 position)
		{
			position.x += dt * 50.f;
			position.y = sin((position.x - WINDOW_WIDTH / 2.f - x) / 20.f) * 50.f + WINDOW_HEIGTH / 2.f + y;

			return position;
		};

		pParticle->SetMoveFunction(sinus);
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
