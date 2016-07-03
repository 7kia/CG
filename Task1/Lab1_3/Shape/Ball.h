#pragma once

#include "StaticShape.h"

#include <vector>
#include <memory>

static const glm::vec3 INNER_COLOR = { 0.f, 0.f, 0.f };

namespace DEFAULT_PARTICLE
{
	const float	RADIUSE = 25.f;
	const float	THIKNESS = 4.f;
}

class CBall
	: public CStaticShape
	, private boost::noncopyable

{
public:
	CBall();
	CBall(const glm::vec2 &position);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
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
//////////////////////////////////////////////////////////////////////
};