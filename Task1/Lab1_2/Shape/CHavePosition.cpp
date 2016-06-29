#include "stdafx.h"
#include "CHavePosition.h"

CHavePosition::CHavePosition()
	: IHavePosition()
{
}

void CHavePosition::SetPosition(const glm::vec2 & position)
{
	m_position = position;
}

void CHavePosition::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

glm::vec2 CHavePosition::GetPosition() const
{
	return m_position;
}

glm::vec2 CHavePosition::GetAbsolutePosition(const glm::vec2 & origin) const
{
	return m_position + origin;
}
