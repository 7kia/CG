#include "stdafx.h"
#include "CompositeShape.h"

ŃCompositeShape::ŃCompositeShape()
	: CShape()
{
}

void ŃCompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}

void ŃCompositeShape::CheckIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}