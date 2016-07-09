#pragma once

#include "StaticShape.h"
#include "DynamicShape.h"

#include <vector>
#include <memory>

static const glm::vec3 INNER_COLOR = { 0.f, 0.f, 0.f };

namespace DEFAULT_BALL
{
	const float	RADIUSE = 10.f;
	const float	THIKNESS = 1.f;
	const float	SPEED = 900.f;
}


class CCircle
	: public CDynamicBody
	, private boost::noncopyable

{
public:
	CCircle(b2World * world);
	CCircle(float radius, const glm::vec2 &position, b2World * world);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
	
	void		SetRadius(float radius);
	float		GetRadius() const;
	//--------------------------------------------
	// IstaticShape
	void		AddToWorld(b2World * world) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void		StrokeCircle() const;
	void		FillCircle() const;
	//--------------------------------------------
	// IStaticShape
	void		CreateBody() override;
	void		CheckParametres() override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Constants
private:
	static const int AMOUNT_POINTS = 360;
//////////////////////////////////////////////////////////////////////
// Data
private:
	float		m_radius = ConvertToBoxCoordinates(DEFAULT_BALL::RADIUSE);
//////////////////////////////////////////////////////////////////////
};