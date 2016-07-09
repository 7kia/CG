#pragma once

#include "Circle.h"

static const glm::vec3 INNER_COLOR = { 0.f, 0.f, 0.f };

class CCircleView
	: public CShape
	, public CCircle
{
public:
	CCircleView();
	CCircleView(float radius, const glm::vec2 &position);

	virtual ~CCircleView() = default;
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
};