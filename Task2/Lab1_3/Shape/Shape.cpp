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

SVertexP3NT2::SVertexP3NT2(const glm::vec3 & position
							, const glm::vec2 & texCoord
							, const glm::vec3 & normal)
	: position(position)
	, texCoord(texCoord)
	, normal(normal)
{
}
