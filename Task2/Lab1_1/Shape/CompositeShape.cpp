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
	CShape::SetFaceColor(color);
}

void �CompositeShape::SetAlpha(float alpha)
{
	for (auto & shape : m_shapes)
	{
		shape->SetAlpha(alpha);
	}
}

void �CompositeShape::SetFaceColor(size_t index, const glm::vec4 & color)
{
	CheckIndex(index);
	m_shapes[index]->SetFaceColor(color);
}

glm::vec4 �CompositeShape::GetFaceColor(size_t index) const
{
	CheckIndex(index);
	return m_shapes[index]->GetFaceColor();
}

void �CompositeShape::SetAlpha(size_t index, float alpha)
{
	CheckIndex(index);
	m_shapes[index]->SetAlpha(alpha);
}

float �CompositeShape::GetAlpha(size_t index) const
{
	CheckIndex(index);
	return m_shapes[index]->GetAlpha();
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