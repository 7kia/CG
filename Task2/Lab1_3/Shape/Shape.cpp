#include "stdafx.h"
#include "Shape.h"

IShape::IShape()
	: IDrawable()
	, IUpdatable()
{
}

CShape::CShape()
	: IShape()
{
}

void CShape::Draw() const
{
	glPushMatrix();// TODO : see neew this method rewrite

	/*
	if (GetFaceColor().a < 0.99f)
	{
		glFrontFace(GL_CW);
		DrawOutputFaces();
		glFrontFace(GL_CCW);
	}
	*/
	
	DrawOutputFaces();

	glPopMatrix();

}