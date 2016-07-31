#include "stdafx.h"
#include "CompositeShape.h"

ÑCompositeShape::ÑCompositeShape()
	: CShape()
{
}

void ÑCompositeShape::SetFaceColor(const glm::vec4 & color)
{
	for (auto & shape : m_shapes)
	{
		shape->SetFaceColor(color);
	}
}

void ÑCompositeShape::SetAlpha(float alpha)
{
	for (auto & shape : m_shapes)
	{
		shape->SetAlpha(alpha);
	}
}

void ÑCompositeShape::Draw() const
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw();
	}
}
