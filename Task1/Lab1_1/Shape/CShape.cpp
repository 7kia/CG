#include "stdafx.h"
#include "CShape.h"


void CShape::SetOutlineColor(const glm::vec3 & color)
{
	m_outlineColor = color;
}

glm::vec3 CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetOrigin(const glm::vec2 & origin)
{
	m_origin = origin;
}

glm::vec2 CShape::GetOrigin() const
{
	return m_origin;
}

