#include "stdafx.h"
#include "DynamicParticle.h"

CDynamicParticle::CDynamicParticle()
	: CHaveVelocity()
	, CParticle()
{
}

void CDynamicParticle::Advance(float dt)
{
	m_velocity += dt * m_acceleration;
	SetPosition(m_velocity + GetPosition());

	m_velocity = glm::vec2();
	m_acceleration = glm::vec2();
}

void CDynamicParticle::ApplyAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration += acceleration;
}
