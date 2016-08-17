#pragma once

#include "Static2DShape.h"
#include "../2DMixins/CHave2DVelocity.h"

class CDynamicBody 
	: public IHave2DVelocity
	, public CStatic2DShape
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
	// IStatic2DShape
	void		Advance(float dt) override;
	//--------------------------------------------
	// IHave2DVelocity
	glm::vec2	GetVelocity() const override;
	void		SetVelocity(const glm::vec2 &GetVelocity) override;
	//--------------------------------------------
	void		ApplyAcceleration(const glm::vec2 & acceleration);
	void		ResetVelocity();
//////////////////////////////////////////////////////////////////////
// Methods
protected:

	//--------------------------------------------
	// IStatic2DShape
	void						CheckParametres() override;
	//--------------------------------------------


};
