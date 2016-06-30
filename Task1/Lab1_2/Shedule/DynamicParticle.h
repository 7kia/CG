#pragma once

#include "../Shape/Particle.h"
#include "CHaveVelocity.h"
// For one constant not need
//namespace
//{
	const glm::vec2 GRAVITY = { 0.f, 0.f };
//}

class CDynamicParticle 
	: public CHaveVelocity
	, public CParticle
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - ������� �� ������� � ���������� ������� Advance.
	// @param acceleration - ���������, ����������� �� �������.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
