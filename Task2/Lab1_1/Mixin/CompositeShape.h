#pragma once

#include "Drawable.h"
#include "../Shape/Shape.h"
#include <vector>


class ŃCompositeShape 
	: public CShape
{
public:
	ŃCompositeShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IHaveFaceColor
	void					SetFaceColor(const glm::vec4 &color) override;

	void					SetAlpha(float alpha) override;
	//--------------------------------------------
	// IShape
	void					Draw() const override final;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};