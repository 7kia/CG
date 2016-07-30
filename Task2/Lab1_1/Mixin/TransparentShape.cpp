#include "stdafx.h"
#include "TransparentShape.h"

CTransparentShape::CTransparentShape()
	: CHaveFaceColor()
	, IShape()
{
}

void CTransparentShape::Draw() const
{
	if (GetFaceColor().a < 0.99f)
	{
		glFrontFace(GL_CW);
		DrawOutputFaces();
		glFrontFace(GL_CCW);
	}
	DrawOutputFaces();
}
