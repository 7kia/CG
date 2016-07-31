#pragma once

#include "../Mixin/Drawable.h"
#include "Shape.h"
#include <vector>


class �CompositeShape 
	: public CShape
{
public:
	�CompositeShape();
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