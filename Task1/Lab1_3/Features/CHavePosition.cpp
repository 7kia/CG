#include "stdafx.h"
#include "CHavePosition.h"

CHavePosition::CHavePosition()
	: IHavePosition()
{
}

void CHavePosition::SetPosition(const glm::vec2 & position)
{
	m_position = ConvertToBoxCoordinates(position);
}

void CHavePosition::SetPosition(float x, float y)
{
	m_position.x = ConvertToBoxCoordinates(x);
	m_position.y = ConvertToBoxCoordinates(y);
}

glm::vec2 CHavePosition::GetPosition() const
{
	return ConvertToNormalCoordinates(m_position);
}

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