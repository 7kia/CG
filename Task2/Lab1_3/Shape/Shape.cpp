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
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
}
