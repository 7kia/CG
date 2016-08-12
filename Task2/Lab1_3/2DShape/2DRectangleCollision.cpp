#include "stdafx.h"
#include "2DRectangleCollision.h"

C2DRectangleCollision::C2DRectangleCollision()
	: CStatic2DShape()
	, CRectangle()
	, CHaveReferenceToC3DShape()
{
	SetReferenceSystemOrigin(glm::vec2());
}

C2DRectangleCollision::C2DRectangleCollision(const glm::vec2 & leftTopPoint
			, SSize size
			, float rotate
			, C3DShape* pVisual)
	: CStatic2DShape()
	, CRectangle(size)
	, CHaveReferenceToC3DShape()
{
	SetPVisual(pVisual);

	SetPosition(leftTopPoint);
	SetRotation(rotate);

	SetReferenceSystemOrigin(glm::vec2());
}

void C2DRectangleCollision::AddToWorld(b2World * world)
{
	CheckParametres();
	CStatic2DShape::AddToWorld(world);

	AddRectangleToBody(m_body
		, SSize(m_width, m_height)
		, GetOrigin());
}

void C2DRectangleCollision::Advance(float dt)
{
	(void)dt;

	auto bodyPosition = GetPosition();//m_pVisual->GetTransform()[3][2]
	auto moveTransform = glm::translate(glm::mat4(), glm::vec3(bodyPosition.x, m_pVisual->GetTransform()[3][1], bodyPosition.y));

	auto resultTransform = moveTransform;
	//auto resultTransform = glm::rotate(moveTransform, GetRotation(), glm::vec3(0.f, 1.f, 0.f));
	m_pVisual->SetTransform(resultTransform);

}



void C2DRectangleCollision::AddRectangleToBody(b2Body *body
	, SSize size
	, const glm::vec2 & shapeOrigin)
{
	if ((size.width < 0.f) || (size.height < 0.f))
	{
		throw std::runtime_error("Size will be more zero!!!");
	}

	// Define the ground box shape.
	b2PolygonShape rectangleShape;

	// Origin body box2d in center by default
	const glm::vec2 shiftOrigin = { -Convert::ToBox(size.width) / 2.f, -Convert::ToBox(size.height) / 2.f };
	rectangleShape.SetAsBox(Convert::ToBox(size.width) / 2.f, Convert::ToBox(size.height) / 2.f
		, b2Vec2(shapeOrigin.x , shapeOrigin.y )
		, 0.f);

	body->CreateFixture(&rectangleShape, 2.f);
}

void C2DRectangleCollision::CheckParametres()
{
	CStatic2DShape::CheckParametres();

	if (m_width == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define rectangle width!!!");

	}

	if (m_height == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define rectangle height!!!");
	}
}
