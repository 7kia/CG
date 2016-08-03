#include "stdafx.h"
#include "Shape.h"

IShape::IShape()
	: IDrawable()
	, IUpdatable()
	, IHaveFaceColor()
{
}

CShape::CShape()
	: IShape()
{
}

void CShape::Draw() const
{
	glPushMatrix();// TODO : see neew this method rewrite

	if (GetFaceColor().a < 0.99f)
	{
		glFrontFace(GL_CW);
		DrawOutputFaces();
		glFrontFace(GL_CCW);
	}
	DrawOutputFaces();

	glPopMatrix();

}

void CShape::SetFaceColor(const glm::vec4 & color)
{
	m_faceColor = color;
}

glm::vec4 CShape::GetFaceColor() const
{
	return m_faceColor;
}

void CShape::SetAlpha(float alpha)
{
	m_faceColor.a = alpha;
}

float CShape::GetAlpha() const
{
	return m_faceColor.a;
}