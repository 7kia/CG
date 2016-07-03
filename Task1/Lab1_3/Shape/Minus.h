#pragma once

#include "CShape.h"
#include "../Features/CHavePosition.h"

// Not blue because green more visible // TODO : see need the color
static const glm::vec3 NEGATIVE_COLOR = { 0.f, 1.0f, 0.f };//{ 0.f, 0.f, 7.f };

static const float WIDTH_SIGN = 5.f;
static const float HEIGHT_SIGN = 25.f;


class CMinus // have heir CPlus
	: public CShape
	, private boost::noncopyable

{
public:
	CMinus();
	CMinus(const glm::vec2 & position);
	~CMinus();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void		Redraw() const override;
	bool		HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
};