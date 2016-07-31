#pragma once

#include "IShape.h"
#include "../Mixin/TransparentShape.h"

class CTetrahedron final 
	: public CTransparentShape
{
public:
	CTetrahedron();
//////////////////////////////////////////////////////////////////////
// Methods
	//--------------------------------------------
	// CTransparentShape
public:
	void Update(float deltaTime) override final;
private:
	
	void DrawOutputFaces() const override final;
	//--------------------------------------------
};