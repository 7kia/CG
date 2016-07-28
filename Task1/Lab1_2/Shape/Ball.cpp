#include "stdafx.h"
#include "Ball.h"

CBall::CBall() 
	: CDynamicBody()
	, IShape()
	, CCircle()
{
	//SetOrigin(glm::vec2(DEFAULT_BALL::RADIUSE / 2.f, DEFAULT_BALL::RADIUSE / 2.f));
}

CBall::CBall(float radius, const glm::vec2 &position)
	: CDynamicBody()
	, IShape()
	, CCircle(radius)
{
	SetPosition(position);
}

void CBall::Advance(float dt)
{
	(void)dt;
	m_visual.SetPosition(GetPosition());

	m_visual.SetOrigin(GetOrigin());
	m_visual.SetReferenceSystemOrigin(GetReferenceSystemOrigin());

}

void CBall::SetVisual()
{
	m_visual.SetRadius(m_radius);
	m_visual.SetPosition(GetPosition());

	m_visual.SetOrigin(GetOrigin());
	m_visual.SetReferenceSystemOrigin(GetReferenceSystemOrigin());

}

void CBall::Redraw() const
{
	m_visual.Redraw();
}

bool CBall::HitTest(const glm::vec2 & point) const
{
	return m_visual.HitTest(point);
}

void CBall::SetOutlineColor(const glm::vec3 & color)
{
	m_visual.SetOutlineColor(color);
}

glm::vec3 CBall::GetOutlineColor() const
{
	return m_visual.GetOutlineColor();
}


void CBall::CheckParametres()
{
	CStaticShape::CheckParametres();
	CDynamicBody::CheckParametres();

	/*
	if (m_radius == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define circle radius!!!")
	}
	*/
	
}

