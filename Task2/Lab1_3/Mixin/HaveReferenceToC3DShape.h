#pragma once

#include "../3DShape/3DShape.h"

class CHaveReferenceToC3DShape
{
public:
	CHaveReferenceToC3DShape() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void				SetPVisual(C3DShape* pVisual);
	C3DShape*			GetPVisual();
//////////////////////////////////////////////////////////////////////
// Data
protected:
	C3DShape*			m_pVisual = nullptr;

};