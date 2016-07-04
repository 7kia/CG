#pragma once

#include "StaticShape.h"

#include <vector>
#include <memory>

static const glm::vec3 INNER_COLOR = { 0.f, 0.f, 0.f };

namespace DEFAULT_BALL
{
	const float	RADIUSE = 10.f;
	const float	THIKNESS = 1.f;
}

class CBall
	: public CStaticShape
	, private boost::noncopyable

{
public:
	CBall();
	CBall(float radius, const glm::vec2 &position);
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
//////////////////////////////////////////////////////////////////////
// Methods
private:
	void		StrokeCircle() const;
	void		FillCircle() const;
//////////////////////////////////////////////////////////////////////
// Constants
private:
	static const int AMOUNT_POINTS = 360;
//////////////////////////////////////////////////////////////////////
// Data
private:
	float		m_radius = DEFAULT_BALL::RADIUSE;
//////////////////////////////////////////////////////////////////////
};