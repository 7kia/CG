#include "stdafx.h"
#include "HaveFaceColor.h"

CHaveFaceColor::CHaveFaceColor()
	: IHaveFaceColor()
{
}

void CHaveFaceColor::SetFaceColor(const glm::vec4 & color)
{
	m_faceColor = color;
}

glm::vec4 CHaveFaceColor::GetFaceColor() const
{
	return m_faceColor;
}

void CHaveFaceColor::SetAlpha(float alpha)
{
	m_faceColor.a = alpha;
}

float CHaveFaceColor::GetAlpha() const
{
	return m_faceColor.a;
}
