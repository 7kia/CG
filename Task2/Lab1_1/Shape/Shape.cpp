#include "stdafx.h"
#include "Shape.h"

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
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));

	if (GetFaceColor().a < 0.99f)
	{
		glFrontFace(GL_CW);
		DrawOutputFaces();
		glFrontFace(GL_CCW);
	}
	DrawOutputFaces();

	glPopMatrix();

}
