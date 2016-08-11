#include "stdafx.h"
#include "CHave2DVelocity.h"

CHave2DVelocity::CHave2DVelocity()
	: IHave2DVelocity()
{
}

glm::vec2 CHave2DVelocity::GetVelocity() const
{
	return m_velocity;
}

void CHave2DVelocity::SetVelocity(const glm::vec2 &velocity)
{
	m_velocity = velocity;
}

/*
glm::vec2 CHave2DVelocity::GetAcceleration() const
{
	return m_acceleration;
}

void CHave2DVelocity::SetAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration = acceleration;
}

*/
