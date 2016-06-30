#include "stdafx.h"
#include "CHaveVelocity.h"

glm::vec2 CHaveVelocity::GetVelocity() const
{
	return m_velocity;
}

void CHaveVelocity::SetVelocity(const glm::vec2 &velocity)
{
	m_velocity = velocity;
}

glm::vec2 CHaveVelocity::GetAcceleration() const
{
	return m_acceleration;
}

void CHaveVelocity::SetAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration = acceleration;
}
