#include "stdafx.h"
#include "Composite3DShape.h"

�Composite3DShape::�Composite3DShape()
	: C3DShape()
{
}

void �Composite3DShape::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));

	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}

	glPopMatrix();
}

void �Composite3DShape::CheckVertexIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}