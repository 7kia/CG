#pragma once

#include "../Shape/StaticShape.h"
#include "../Shape/Ball.h"
#include "../Shape/Rectangle.h"

class CPhysicalSystem;

static const float SHIFT_BALL = 50.f;

class CGun final
	: public CStaticShape
{
public:
	CGun();
	~CGun();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void				Redraw() const override;
	bool				HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------

	void				Shoot(CPhysicalSystem * system, const glm::vec2 & direction);
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<std::shared_ptr<CStaticShape>>		m_components;
};