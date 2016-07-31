#pragma once

#include "IShape.h"
#include "../Mixin/TransparentShape.h"
#include "../Mixin/HaveVertex.h"

class CTriangle final
	: public CTransparentShape
	, public CHaveVertex
{
public:
	CTriangle();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CTransparentShape
	void					Update(float deltaTime) override final;
private:
	void					DrawOutputFaces() const override final;
	//--------------------------------------------
};
