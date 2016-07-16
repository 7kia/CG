#include "stdafx.h"
#include "DynamicParticle.h"

CDynamicParticle::CDynamicParticle()
	: CHaveVelocity()
	, CParticle()
{
}

void CDynamicParticle::Advance(float dt)
{

	m_velocity += dt * m_acceleration * 20.f;

	
	
	// friction
	if (glm::length(m_velocity) > MIN_VELOCITY)
	{
		const glm::vec2 frictionPower = -GetFrictionPower(GetVelocity());
		const glm::vec2	frictionAcceleration = frictionPower / GetMass();
		m_velocity -= frictionAcceleration;
		if (frictionAcceleration != glm::vec2())
		{
			const float p1 = glm::length(m_velocity);
			const float p2 = glm::length(frictionAcceleration);
			const glm::vec2 frictionPower = GetFrictionPower(GetVelocity());

		}

		// friction
		if (glm::length(m_velocity) > MIN_VELOCITY)
		{
			const float p1 = glm::length(m_velocity);
			const float p2 = glm::length(frictionAcceleration);

			const glm::vec2 frictionPower = GetFrictionPower(GetVelocity());

		}
	}
	
	SetPosition(m_velocity + GetPosition());

	if (glm::length(m_velocity) > MIN_VELOCITY)
	{
		m_velocity = glm::vec2();
	}

	m_acceleration = glm::vec2();
}

void CDynamicParticle::ApplyAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration += acceleration;
}

glm::vec2 GetFrictionPower(const glm::vec2 & velocity)
{
	float valueVelocity = glm::length(velocity);
	return COEFICIENT_FRICTION * valueVelocity * valueVelocity * glm::normalize(velocity) / 2.f;
}
