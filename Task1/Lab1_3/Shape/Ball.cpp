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

void CBall::AddToWorld(b2World * world)
{	
	CheckParametres();
	CStaticShape::AddToWorld(world);

	SetVisual();
	AddCircleToBody(m_body, m_radius);
}

void CBall::Advance(float dt)
{
	(void)dt;
	m_visual.SetPosition(GetPosition());
	m_visual.SetRotation(GetRotation());

	m_visual.SetOrigin(GetOrigin());
	m_visual.SetReferenceSystemOrigin(GetReferenceSystemOrigin());

}

void CBall::SetVisual()
{
	m_visual.SetRadius(m_radius);
	m_visual.SetPosition(GetPosition());
	m_visual.SetRotation(GetRotation());

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

void CBall::AddCircleToBody(b2Body *body, float radius)
{
	b2CircleShape circleShape;
	circleShape.m_radius = Convert::ToBox(radius);

	b2FixtureDef circle;
	circle.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	circle.density = 1.0f;

	// Override the default friction.
	circle.friction = 0.3f;

	circle.restitution = 0.5f;

	// Add the shape to the body.
	body->CreateFixture(&circle);// TODO : magic value

	//m_body->CreateFixture(&circle, 2);
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

