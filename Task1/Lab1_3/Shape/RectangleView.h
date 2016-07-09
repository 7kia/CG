#pragma once

#include "Rectangle.h"

class CRectangleView
	: public CShape
	, public CRectangle
{
public:
	CRectangleView();
	CRectangleView(SSize size, const glm::vec2 & position);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void				Redraw() const override;
	bool				HitTest(const glm::vec2 &point) const override;
	//--------------------------------------------
};