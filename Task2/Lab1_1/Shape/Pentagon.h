#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Triangle.h"

class CPentagon final
	: public �CompositeShape
{
public:
	CPentagon();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	//--------------------------------------------
};
