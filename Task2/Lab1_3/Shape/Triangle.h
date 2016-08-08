#pragma once

#include "Shape.h"
#include "../Mixin/HaveVertex.h"

class CTriangle final
	: public CShape
{
public:
	CTriangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
private:
	void					DrawOutputFaces() const override final;
	//--------------------------------------------
};
