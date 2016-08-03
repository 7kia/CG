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
	CShape::SetFaceColor(color);
}

void ÑCompositeShape::SetAlpha(float alpha)
{
	for (auto & shape : m_shapes)
	{
		shape->SetAlpha(alpha);
	}
}

void ÑCompositeShape::SetFaceColor(size_t index, const glm::vec4 & color)
{
	CheckIndex(index);
	m_shapes[index]->SetFaceColor(color);
}

glm::vec4 ÑCompositeShape::GetFaceColor(size_t index) const
{
	CheckIndex(index);
	return m_shapes[index]->GetFaceColor();
}

void ÑCompositeShape::SetAlpha(size_t index, float alpha)
{
	CheckIndex(index);
	m_shapes[index]->SetAlpha(alpha);
}

float ÑCompositeShape::GetAlpha(size_t index) const
{
	CheckIndex(index);
	return m_shapes[index]->GetAlpha();
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