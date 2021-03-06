#include "stdafx.h"
#include "CHavePosition.h"

CHavePosition::CHavePosition()
	: IHavePosition()
{
}

void CHavePosition::SetPosition(const glm::vec2 & position)
{
	m_position = position;////Convert::ToBox()
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

float Convert::ToBox(const float value)
{
	return value / SCALE;
}

glm::vec2 Convert::ToBox(const const glm::vec2 & value)
{
	return glm::vec2(Convert::ToBox(value.x), Convert::ToBox(value.y));
}

float Convert::ToNormal(const float value)
{
	return value * SCALE;
}

glm::vec2 Convert::ToNormal(const glm::vec2 & value)
{
	return glm::vec2(Convert::ToNormal(value.x), Convert::ToNormal(value.y));
}