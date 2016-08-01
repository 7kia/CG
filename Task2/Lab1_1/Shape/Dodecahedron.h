#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Pentagon.h"

class CDodecahedron final
	: public ÑCompositeShape
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
