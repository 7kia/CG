#pragma once

#include "../Shape/Particle.h"

// For one constant not need
//namespace
//{
	const glm::vec2 GRAVITY = { 0.f, 0.f };
//}

class CDynamicParticle : public CParticle
{
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// @param dt - ������� �� ������� � ���������� ������� Advance.
	// @param acceleration - ���������, ����������� �� �������.
	void		Advance(float dt, const glm::vec2 &acceleration);

	glm::vec2	GetVelocity() const;
	void		SetVelocity(const glm::vec2 &GetVelocity);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	glm::vec2	m_velocity;
	//////////////////////////////////////////////////////////////////////
};
