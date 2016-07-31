#pragma once

#include "Shape.h"
#include "../Mixin/CompositeShape.h"
#include "Triangle.h"

class CTetrahedron final 
	: public ŃCompositeShape
{
public:
	CTetrahedron();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// ŃCompositeShape
	void Update(float deltaTime) override final;
};