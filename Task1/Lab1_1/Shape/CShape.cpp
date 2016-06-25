#include "stdafx.h"
#include "CShape.h"

CShape::~CShape()
{
}

void CShape::SetOutlineColor(const glm::vec3 & color)
{
	m_outlineColor = color;
}

glm::vec3 CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
