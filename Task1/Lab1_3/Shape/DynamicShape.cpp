#include "stdafx.h"
#include "DynamicShape.h"

void CDynamicBody::Advance(float dt)
{
	m_velocity += dt * m_acceleration;
	SetPosition(m_velocity + GetPosition());

	//m_velocity = glm::vec2();// TODO : see need reset this
	//m_acceleration = glm::vec2();
}

void CDynamicBody::ApplyAcceleration(const glm::vec2 & acceleration)
{
	m_acceleration += acceleration;
}
