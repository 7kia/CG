#include "stdafx.h"
#include "CHave2DPosition.h"


CHave2DPosition::CHave2DPosition()
	: IHave2DPosition()
{
}

void CHave2DPosition::SetPosition(const glm::vec2 & position)
{
	m_position = Convert::ToBox(position);
}

void CHave2DPosition::SetPosition(float x, float y)
{
	m_position.x = Convert::ToBox(x);
	m_position.y = Convert::ToBox(y);
}

glm::vec2 CHave2DPosition::GetPosition() const
{
	return Convert::ToNormal(m_position);
}
