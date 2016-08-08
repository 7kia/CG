#include "stdafx.h"
#include "CompositeShape.h"

�CompositeShape::�CompositeShape()
	: IShape()
{
}

void �CompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}

void �CompositeShape::CheckVertexIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}