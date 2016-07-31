#pragma once

#include "IShape.h"
#include "../Mixin/CompositeShape.h"
#include "Triangle.h"

class CTetrahedron final 
	: public �CompositeShape
{
public:
	CTetrahedron();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// �CompositeShape
	void Update(float deltaTime) override final;
};