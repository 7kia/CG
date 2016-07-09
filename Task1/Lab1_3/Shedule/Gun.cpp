#include "stdafx.h"
#include "Gun.h"

CGun::CGun(b2World * world)
	: CStaticShape(world)
{
	//m_defBody.type = b2_dynamicBody;

	//m_body = world->CreateBody(&m_defBody);

	// Rectangle
	// Define the ground box shape.
	b2PolygonShape rectangleShape;

	// The extents are the half-widths of the box.
	rectangleShape.SetAsBox(40.f / SCALE, 15.f / SCALE);//SetAsBox(50.0f, 10.0f);

															   // Add the ground fixture to the ground body.
	m_body->CreateFixture(&rectangleShape, 2.f);



	// Circle
	b2CircleShape circleShape;
	circleShape.m_radius = ConvertToBoxCoordinates(25.f / SCALE);

	b2FixtureDef circle;
	circle.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	circle.density = 1.0f;

	// Override the default friction.
	circle.friction = 0.3f;

	// Add the shape to the body.
	m_body->CreateFixture(&circle);// TODO : magic value

	/*
	m_body->GetFixtureList()

	auto pCircle = std::make_shared<CCircle>(world);
	pCircle->SetRadius(25.f);
	m_components.push_back(pCircle);

	auto pTrunk = std::make_shared<CRectangle>(world);
	pTrunk->SetWidth(40.f);
	pTrunk->SetHeight(15.f);
	pTrunk->SetPosition(glm::vec2(DEFAULT_BALL::RADIUSE + pTrunk->GetHeight() - DEFAULT_GUN::SHIFT_TRUNK 
									, -pTrunk->GetHeight() / 2.f));
	pTrunk->SetShapeOrigin(glm::vec2(-pTrunk->GetPosition().x
									, pTrunk->GetHeight() / 2.f));

	m_components.push_back(pTrunk);

	*/
}

CGun::~CGun()
{
}

void CGun::Redraw() const
{
	for (const auto & component : m_components)
	{
		component->Redraw();
	}
}

bool CGun::HitTest(const glm::vec2 & point) const
{
	(void)point;
	return false;
}

void CGun::SetPosition(const glm::vec2 & position)
{
	CStaticShape::SetPosition(position);

	for (auto & component : m_components)
	{
		component->SetReferenceSystemOrigin(position + m_referenceSystemOrigin);
	}
}

void CGun::SetPosition(float x, float y)
{
	SetPosition(glm::vec2(x, y));
}

glm::vec2 CGun::GetCenterPosition(const glm::vec2 & origin) const// TODO : rewrite right for other classes
{
	return GetCenterPosition() + origin;
}

glm::vec2 CGun::GetCenterPosition() const
{
	return GetPosition() + m_referenceSystemOrigin;
}

void CGun::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	CHavePosition::SetReferenceSystemOrigin(origin);

	for (auto & component : m_components)
	{
		component->SetReferenceSystemOrigin(origin);
	}
}

void CGun::SetRotation(float rotation)
{
	//CRotatable::SetRotation(rotation);

	for (auto & compoenent : m_components)
	{
		compoenent->SetRotation(rotation);
	}
}
