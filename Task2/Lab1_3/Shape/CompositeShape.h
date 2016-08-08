#pragma once

#include "../Mixin/Drawable.h"
#include "Shape.h"
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
	// IShape
	void					Draw() const override final;
	//--------------------------------------------
private:
	void					CheckIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};