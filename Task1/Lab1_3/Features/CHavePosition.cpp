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
	return m_position + m_referenceSystemOrigin;
}

void CHavePosition::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	m_referenceSystemOrigin = origin;
}

glm::vec2 CHavePosition::GetReferenceSystemOrigin() const
{
	return m_referenceSystemOrigin;
}

void CHavePosition::SetShapeOrigin(const glm::vec2 & origin)
{
	m_shapeOrigin = origin;
}

glm::vec2 CHavePosition::GetShapeOrigin() const
{
	return m_shapeOrigin;
}
