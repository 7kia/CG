#pragma once

#include "../Mixin/Drawable.h"
#include "Shape.h"
#include <vector>


class ÑCompositeShape 
	: public CShape
{
public:
	ÑCompositeShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IShape
	void					Draw() const override;
	//--------------------------------------------
private:
	void					CheckVertexIndex(size_t index) const;

//////////////////////////////////////////////////////////////////////
// Data
public:
	std::vector<IBodyUniquePtr>		m_shapes;
};