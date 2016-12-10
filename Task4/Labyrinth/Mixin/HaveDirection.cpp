#include "stdafx.h"
#include "HaveDirection.h"

CHaveDirection::CHaveDirection()
	: IHaveDirection()
{
}

CHaveDirection::CHaveDirection(const glm::vec3 & value)
{
	SetDirection(value);
}

void CHaveDirection::SetDirection(const glm::vec3 & value)
{
	m_direction.x = value.x;
	m_direction.y = value.y;
	m_direction.z = value.z;
}

glm::vec4 CHaveDirection::GetDirection() const
{
	return m_direction;
}
