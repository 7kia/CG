#include "stdafx.h"
#include "DynamicParticle.h"

void CDynamicParticle::Advance(float dt, const glm::vec2 &acceleration)
{
	m_velocity += dt * acceleration;
	SetPosition(m_velocity + GetPosition());
}

glm::vec2 CDynamicParticle::GetVelocity() const
{
	return m_velocity;
}

void CDynamicParticle::SetVelocity(const glm::vec2 &velocity)
{
	m_velocity = velocity;
}
