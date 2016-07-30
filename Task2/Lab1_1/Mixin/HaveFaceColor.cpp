#include "stdafx.h"
#include "HaveFaceColor.h"

CHaveFaceColor::CHaveFaceColor()
	: IHaveFaceColor()
{
}

void CHaveFaceColor::SetFaceColor(const glm::vec3 & color)
{
	m_faceColor = color;
}

glm::vec3 CHaveFaceColor::GetFaceColor() const
{
	return m_faceColor;
}
