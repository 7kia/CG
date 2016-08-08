#include "stdafx.h"
#include "CompositeShape.h"

�CompositeShape::�CompositeShape()
	: CShape()
{
}

void �CompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}

void �CompositeShape::CheckIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}