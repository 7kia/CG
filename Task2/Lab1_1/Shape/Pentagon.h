#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Triangle.h"

namespace PentagonSpace
{
	const float HEIGHT_TRIANGLE = 0.80901f;
	const float SIDE = 1.1755164f;
}

class CPentagon final
	: public ŃCompositeShape
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
