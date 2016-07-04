#pragma once

#include "../Shape/StaticShape.h"
#include "../Shape/Ball.h"
#include "../Shape/Rectangle.h"

class CPhysicalSystem;

namespace DEFAULT_GUN
{
	static const float SHIFT_BALL = 50.f;
	static const float SHIFT_TRUNK = 5.f;

}

class CGun final
	: public CStaticShape
{
public:
	CGun(b2World * world);
	~CGun();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void				Redraw() const override;
	bool				HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
	// CHavePosition
	void				SetPosition(const glm::vec2 & position) override;
	void				SetPosition(float x, float y) override;

	glm::vec2			GetCenterPosition(const glm::vec2 & origin) const override;
	glm::vec2			GetCenterPosition() const override;

	void				SetOrigin(const glm::vec2 & origin) override;
	//--------------------------------------------

	void				Shoot(CPhysicalSystem * system, const glm::vec2 & mousePosition);
	glm::vec2			GetDirection(const glm::vec2 & point);
//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<std::shared_ptr<CStaticShape>>		m_components;
};