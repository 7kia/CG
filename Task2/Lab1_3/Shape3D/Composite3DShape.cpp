#include "stdafx.h"
#include "Composite3DShape.h"

ÑComposite3DShape::ÑComposite3DShape()
	: I3DShape()
{
}

void ÑComposite3DShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}

void ÑComposite3DShape::CheckVertexIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_shapes.size()))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}