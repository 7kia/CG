#pragma once

#include "Shape.h"
#include "../Mixin/CompositeShape.h"
#include "Triangle.h"

class CTetrahedron final 
	: public ÑCompositeShape
{
public:
	CTetrahedron();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// ÑCompositeShape
	void Update(float deltaTime) override final;
};