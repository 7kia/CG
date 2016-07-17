#pragma once

#include "../Shape/Particle.h"
#include "../Features/CHaveVelocity.h"

static const float COEFICIENT_FRICTION = 0.5f * 1.60217662e-9f / 0.2f;// for sphere
static const float MIN_VELOCITY = 0.5f;
static const float MIN_ACCELERATION = 19.0e+0f;

glm::vec2 GetFrictionPower(const glm::vec2 & velocity);

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
	// @param dt - разница во времени с предыдущим вызовом Advance.
	// @param acceleration - ускорение, действующее на частицу.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
