#pragma once

#include "Composite3DShape.h"
#include "../Mixin/HaveVertex.h"
#include "3DTriangle.h"

class C3DRectangle final
	: public ÑComposite3DShape
	, public CHaveReferenceVertex
{
public:
	C3DRectangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CIdentity3DShape
	//--------------------------------------------
private:
	void					UpdateReference() override final;
};
