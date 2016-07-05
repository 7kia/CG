#pragma once

#include "../Shape/StaticShape.h"
#include "../Features/CHaveVelocity.h"
// For one constant not need
//namespace
//{
	const glm::vec2 GRAVITY = { 0.f, -10.f };
//}

class CDynamicBody 
	: public IHaveVelocity
	, public CStaticShape
{
public:
	CDynamicBody();
	virtual ~CDynamicBody() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - разница во времени с предыдущим вызовом Advance.
	// @param acceleration - ускорение, действующее на частицу.
	//--------------------------------------------
	// IStaticShape

	void		Advance(float dt) override;
	//--------------------------------------------
	// IHaveVelocity
	glm::vec2	GetVelocity() const override;
	void		SetVelocity(const glm::vec2 &GetVelocity) override;
	//--------------------------------------------
	void		ApplyAcceleration(const glm::vec2 & acceleration);


};
