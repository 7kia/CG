#pragma once

#include "glm/vec2.hpp"

class CHaveVelocity
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	glm::vec2	GetVelocity() const;
	void		SetVelocity(const glm::vec2 &GetVelocity);

	glm::vec2	GetAcceleration() const;
	void		SetAcceleration(const glm::vec2 &acceleration);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2	m_velocity;
	glm::vec2	m_acceleration;
//////////////////////////////////////////////////////////////////////
};