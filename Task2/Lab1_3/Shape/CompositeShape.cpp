#include "stdafx.h"
#include "CompositeShape.h"

ÑCompositeShape::ÑCompositeShape()
	: CShape()
{
}

void ÑCompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}

void ÑCompositeShape::CheckIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}