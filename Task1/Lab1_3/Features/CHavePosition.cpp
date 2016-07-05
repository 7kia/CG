#include "stdafx.h"
#include "CHavePosition.h"

CHavePosition::CHavePosition()
	: IHavePosition()
{
}

/*
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

*/

float ConvertToBoxCoordinates(const float value)
{
	return value / SCALE;
}

glm::vec2 ConvertToBoxCoordinates(const const glm::vec2 & value)
{
	return glm::vec2(ConvertToBoxCoordinates(value.x), ConvertToBoxCoordinates(value.y));
}

float ConvertToNormalCoordinates(const float value)
{
	return value * SCALE;
}

glm::vec2 ConvertToNormalCoordinates(const glm::vec2 & value)
{
	return glm::vec2(ConvertToNormalCoordinates(value.x), ConvertToNormalCoordinates(value.y));
}


void CHavePosition::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	m_referenceSystemOrigin = ConvertToBoxCoordinates(origin);
}

glm::vec2 CHavePosition::GetReferenceSystemOrigin() const
{
	return ConvertToNormalCoordinates(m_referenceSystemOrigin);
}

void CHavePosition::SetShapeOrigin(const glm::vec2 & origin)
{
	m_shapeOrigin = ConvertToBoxCoordinates(origin);
}

glm::vec2 CHavePosition::GetShapeOrigin() const
{
	return ConvertToNormalCoordinates(m_shapeOrigin);
}
