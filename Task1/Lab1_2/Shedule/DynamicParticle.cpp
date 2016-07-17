#include "stdafx.h"
#include "DynamicParticle.h"

CDynamicParticle::CDynamicParticle()
	: CHaveVelocity()
	, CParticle()
{
}

void CDynamicParticle::Advance(float dt)
{

	m_velocity += dt * m_acceleration * 1.f;


	
	

	if (glm::length(m_velocity) < MIN_VELOCITY)
	{
		m_velocity = glm::vec2();
	}
	else
	{
		//const glm::vec2 acceleration = GetFrictionPower(m_velocity) / GetMass();
		//m_velocity += dt * acceleration;
		m_velocity *= 0.8;
	}

	SetPosition(m_velocity + GetPosition());

	//m_velocity = glm::vec2();
	m_acceleration = glm::vec2();
}

void CDynamicParticle::ApplyAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration += acceleration;
}

glm::vec2 GetFrictionPower(const glm::vec2 & velocity)
{
	float valueVelocity = glm::length(velocity);
	return -COEFICIENT_FRICTION * velocity * velocity;// valueVelocity * valueVelocity * glm::normalize(velocity) / 2.f;
}
