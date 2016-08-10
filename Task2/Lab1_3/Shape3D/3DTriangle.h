#pragma once

#include "3DShape.h"
#include "../Mixin/HaveVertex.h"

class C3DTriangle final
	: public C3DShape
{
public:
	C3DTriangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// C3DShape
	void					Update(float deltaTime) override final;
private:
	void					DrawOutputFaces() const override final;
	//--------------------------------------------
};
