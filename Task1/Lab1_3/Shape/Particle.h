#pragma once

#include "CShape.h"

#include <vector>
#include <memory>

static const glm::vec3 INNER_COLOR = { 0.f, 0.f, 0.f };

namespace DEFAULT_PARTICLE
{
	const float	RADIUSE = 25.f;
	const float	THIKNESS = 4.f;
}

class CParticle
	: public CShape
	, private boost::noncopyable

{
public:
	CParticle();
	CParticle(const glm::vec2 &position, bool isNegative = false);
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