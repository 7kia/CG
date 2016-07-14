#pragma once

#include "../Shape/Particle.h"
#include "../Features/CHaveVelocity.h"

class CDynamicParticle 
	: public CHaveVelocity
	, public CParticle
{
	CDynamicParticle();
	virtual ~CDynamicParticle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - разница во времени с предыдущим вызовом Advance.
	// @param acceleration - ускорение, действующее на частицу.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
