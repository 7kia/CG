#include "stdafx.h"
#include "HavePosition.h"

CHavePosition::CHavePosition()
	: IHavePosition()
{
}

void CHavePosition::SetPosition(const glm::vec3 & value)
{
	m_position.x = value.x;
	m_position.y = value.y;
	m_position.z = value.z;
}

glm::vec3 CHavePosition::GetPosition() const
{
	return{ m_position.x, m_position.y, m_position.z };
}

CHavePosition::CHavePosition(const glm::vec3 & value)
{
	SetPosition(value);
}

void CHavePosition::Move(const glm::vec3 & value)
{
	SetPosition(GetPosition() + value);
}
