#pragma once

#include "IShape.h"
#include "../Mixin/HaveVertex.h"

class CRectangle final
	: public CShape
{
public:
	CRectangle();
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
