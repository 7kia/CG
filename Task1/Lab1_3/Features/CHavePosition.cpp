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

glm::vec2 CHavePosition::GetCenterPosition(const glm::vec2 & origin) const
{
	return m_position + origin;
}

glm::vec2 CHavePosition::GetCenterPosition() const
{
	return m_position + m_origin;
}

void CHavePosition::SetOrigin(const glm::vec2 & origin)
{
	m_origin = origin;
}

glm::vec2 CHavePosition::GetOrigin() const
{
	return m_origin;
}
