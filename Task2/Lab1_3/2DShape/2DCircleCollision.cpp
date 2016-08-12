#include "stdafx.h"
#include "2DCircleCollision.h"

C2DCircleCollision::C2DCircleCollision()
	: CDynamicBody()
	, CCircle()
	, CHaveReferenceToC3DShape()
{
	//SetOrigin(glm::vec2(DEFAULT_BALL::RADIUSE / 2.f, DEFAULT_BALL::RADIUSE / 2.f));
}

C2DCircleCollision::C2DCircleCollision(float radius, const glm::vec2 &position, C3DShape* pVisual)
	: CDynamicBody()
	, CCircle(radius)
	, CHaveReferenceToC3DShape()
{
	SetPVisual(pVisual);
	SetPosition(position);
}

void C2DCircleCollision::AddToWorld(b2World * world)
{	
	CheckParametres();
	CStatic2DShape::AddToWorld(world);

	AddCircleToBody(m_body, m_radius);
}

void C2DCircleCollision::Advance(float dt)
{
	(void)dt;

	auto bodyPosition = GetPosition();//m_pVisual->GetTransform()[3][2]
	auto moveTransform = glm::translate(glm::mat4(), glm::vec3(bodyPosition.x, m_pVisual->GetTransform()[3][1], bodyPosition.y));

	auto resultTransform = moveTransform;
	//auto resultTransform = glm::rotate(moveTransform, GetRotation(), glm::vec3(0.f, 1.f, 0.f));
	m_pVisual->SetTransform(resultTransform);

}

void C2DCircleCollision::AddCircleToBody(b2Body *body, float radius)
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

void C2DCircleCollision::CheckParametres()
{
	CStatic2DShape::CheckParametres();
	CDynamicBody::CheckParametres();

	/*
	if (m_radius == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define circle radius!!!")
	}
	*/
	
}

