#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Pentagon.h"

class CDodecahedron final
	: public ŃCompositeShape
{
public:
	CDodecahedron();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	//--------------------------------------------
};
