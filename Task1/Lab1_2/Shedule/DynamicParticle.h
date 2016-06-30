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
	// @param dt - разница во времени с предыдущим вызовом Advance.
	// @param acceleration - ускорение, действующее на частицу.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
