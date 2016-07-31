#include "stdafx.h"
#include "CompositeShape.h"

�CompositeShape::�CompositeShape()
	: CShape()
{
}

void �CompositeShape::SetFaceColor(const glm::vec4 & color)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFaceColor(color);
	}
}

void �CompositeShape::SetAlpha(float alpha)
{
	for (auto & shape : m_shapes)
	{
		shape->SetAlpha(alpha);
	}
}

void �CompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}
