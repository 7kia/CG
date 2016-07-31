#include "stdafx.h"
#include "IShape.h"

IShape::IShape()
	: IDrawable()
	, IUpdatable()
{
}

CShape::CShape()
	: CHaveFaceColor()
	, IShape()
{
}

void CShape::Draw() const
{
	if (GetFaceColor().a < 0.99f)
	{
		glFrontFace(GL_CW);
		DrawOutputFaces();
		glFrontFace(GL_CCW);
	}
	DrawOutputFaces();
}
