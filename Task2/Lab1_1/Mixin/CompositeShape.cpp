#include "stdafx.h"
#include "CompositeShape.h"

ŃCompositeShape::ŃCompositeShape()
	: CShape()
{
}

void ŃCompositeShape::SetFaceColor(const glm::vec4 & color)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFaceColor(color);
	}
}

void ŃCompositeShape::SetAlpha(float alpha)
{
	for (auto & shape : m_shapes)
	{
		shape->SetAlpha(alpha);
	}
}

void ŃCompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}
