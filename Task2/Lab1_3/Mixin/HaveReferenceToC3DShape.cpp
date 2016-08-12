#include "stdafx.h"
#include "HaveReferenceToC3DShape.h"

void CHaveReferenceToC3DShape::SetPVisual(C3DShape * pVisual)
{
	m_pVisual = pVisual;
}

C3DShape * CHaveReferenceToC3DShape::GetPVisual()
{
	return m_pVisual;
}
