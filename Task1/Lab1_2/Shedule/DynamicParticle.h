#pragma once

#include "../Shape/Particle.h"
#include "../Features/CHaveVelocity.h"

class CDynamicParticle 
	: public CHaveVelocity
	, public CParticle
{
public:
	CDynamicParticle();
	virtual ~CDynamicParticle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - ������� �� ������� � ���������� ������� Advance.
	// @param acceleration - ���������, ����������� �� �������.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
