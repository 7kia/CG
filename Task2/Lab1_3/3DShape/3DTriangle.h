#pragma once

#include "3DShape.h"
#include "../Mixin/HaveVertex.h"

class C3DTriangle final
	: public CIdentity3DShape
{
public:
	C3DTriangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CIdentity3DShape
private:
	void					DrawOutputFaces() const override final;
	//--------------------------------------------
};
