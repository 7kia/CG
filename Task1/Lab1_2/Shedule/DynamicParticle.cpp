#include "stdafx.h"
#include "DynamicParticle.h"

void CDynamicParticle::Advance(float dt, const glm::vec2 &acceleration)
{
	m_lifetime -= dt;
	m_velocity += dt * acceleration;
	SetPosition(m_velocity + GetPosition());
}

bool CDynamicParticle::IsAlive() const
{
	const float epsilon = std::numeric_limits<float>::epsilon();
	return m_lifetime > epsilon;
}

glm::vec2 CDynamicParticle::GetVelocity() const
{
	return m_velocity;
}

void CDynamicParticle::SetVelocity(const glm::vec2 &velocity)
{
	m_velocity = velocity;
}

void CDynamicParticle::SetLifetime(float lifetime)
{
	m_lifetime = lifetime;
}
