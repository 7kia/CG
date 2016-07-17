#pragma once

#include "../Shape/Particle.h"
#include "../Features/CHaveVelocity.h"
#include "../Shedule/StaticParticle.h"

static const float COEFICIENT_FRICTION = 1.60217662e-9f / 2.f;// for sphere
static const float MIN_VELOCITY = 0.5f;
static const float MIN_ACCELERATION = 19.0e+0f;

glm::vec2 GetFrictionPower(const glm::vec2 & velocity);

class CDynamicParticle 
	: public CStaticParticle
{
public:
	CDynamicParticle();
	virtual ~CDynamicParticle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - разница во времени с предыдущим вызовом Advance.
	// @param acceleration - ускорение, действующее на частицу.
	void		Advance(float dt) override;

	void		ApplyAcceleration(const glm::vec2 & acceleration) override;

};
