#pragma once

#include "../Shape/Particle.h"
#include "../Features/Advancable.h"
#include "../Features/CHaveVelocity.h"
#include <functional>

// TODO : see might need trensfer to other place
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGTH = 600;

using MoveFunction = std::function<glm::vec2(float, glm::vec2)>;

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
	void									SetMoveFunction(std::shared_ptr<MoveFunction> function);
	void									ApplyAcceleration(const glm::vec2 & acceleration) override;
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::shared_ptr<MoveFunction>		m_moveFunction = nullptr;
};