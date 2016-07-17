#pragma once

#include "../Shape/Particle.h"
#include "../Features/Advancable.h"
#include "../Features/CHaveVelocity.h"
#include <functional>

class CStaticParticle
	: public CParticle
	, public IAdvancable
	, public CHaveVelocity
{
public:
	CStaticParticle();
	virtual ~CStaticParticle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void									Advance(float dt) override;
	void									SetMoveFunction(std::function<glm::vec2(float, glm::vec2)> function);
	void									ApplyAcceleration(const glm::vec2 & acceleration) override;
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::function<glm::vec2(float, glm::vec2)>		m_moveFunction = nullptr;
};