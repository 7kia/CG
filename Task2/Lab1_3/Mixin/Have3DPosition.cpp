#include "stdafx.h"
#include "Have3DPosition.h"

CHave3DPosition::CHave3DPosition()
	: IHave3DPosition()
{
}

void CHave3DPosition::SetPosition(const glm::vec3 & value)
{
	m_position.x = value.x;
	m_position.y = value.y;
	m_position.z = value.z;
}

glm::vec3 CHave3DPosition::GetPosition() const
{
	return{ m_position.x, m_position.y, m_position.z };
}

CHave3DPosition::CHave3DPosition(const glm::vec3 & value)
{
	SetPosition(value);
}

void CHave3DPosition::Move(const glm::vec3 & value)
{
	SetPosition(GetPosition() + value);
}
