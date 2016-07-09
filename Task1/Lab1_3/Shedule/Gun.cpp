#include "stdafx.h"
#include "Gun.h"

CGun::CGun(b2World * world)
	: CStaticShape(world)
{
	//m_defBody.type = b2_dynamicBody;

	//m_body = world->CreateBody(&m_defBody);

	// Rectangle
	// Define the ground box shape.
	

	/*
	//m_body->GetFixtureList()

	auto pCircle = std::make_shared<CBall>(world);
	pCircle->SetRadius(25.f);
	m_components.push_back(pCircle);

	auto pTrunk = std::make_shared<CWall>(world);
	pTrunk->SetWidth(40.f);
	pTrunk->SetHeight(15.f);
	pTrunk->SetPosition(glm::vec2(DEFAULT_BALL::RADIUSE + pTrunk->GetHeight() - DEFAULT_GUN::SHIFT_TRUNK 
									, -pTrunk->GetHeight() / 2.f));
	pTrunk->SetShapeOrigin(glm::vec2(-pTrunk->GetPosition().x
									, pTrunk->GetHeight() / 2.f));

	m_components.push_back(pTrunk);

	//*/
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
	m_body->SetFixedRotation(rotation);

	for (auto & compoenent : m_components)
	{
		compoenent->SetRotation(rotation);
	}
}

void CGun::Rotate(const glm::vec2 & mousePosition)
{
	const glm::vec2 direction = GetDirection(mousePosition);

	const float dotProduct = glm::dot(direction, glm::vec2(1.f, 0.f));
	const float lengthDirectionVector = glm::length(direction);
	const float angle = acos(dotProduct) / lengthDirectionVector;
	SetRotation(direction.y > 0 ? angle : -angle);
}

void CGun::AddToWorld(b2World * world)
{
	CheckParametres();
	CStaticShape::AddToWorld(world);
	CreateBody(40.f, 15.f, 25.f);
}


void CGun::CheckParametres()
{
	CStaticShape::CheckParametres();

}

void CGun::CreateBody(float trunkWidth
					, float trunkHeigth
					, float baseRadius)
{
	CWall::AddRectangleToBody(m_body
									, SSize(trunkWidth, trunkHeigth) 
									, 0.f
									, glm::vec2(DEFAULT_BALL::RADIUSE - DEFAULT_GUN::SHIFT_TRUNK// - trunkWidth
												, 0.f) );

	CBall::AddCircleToBody(m_body, baseRadius);
}
