#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Triangle.h"

class CRectangle final
	: public ÑCompositeShape
{
public:
	CRectangle();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	//--------------------------------------------
};
