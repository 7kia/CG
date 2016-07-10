#include "stdafx.h"
#include "Gun.h"

CGun::CGun()
	: CStaticShape()
{
}

CGun::~CGun()
{
}

void CGun::Redraw() const
{
	for (const auto & component : m_visual)
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

	for (auto & component : m_visual)
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
	CHaveOrigin::SetReferenceSystemOrigin(origin);

	for (auto & component : m_visual)
	{
		component->SetReferenceSystemOrigin(origin);
	}
}

void CGun::SetRotation(float rotation)
{
	//CRotatable::SetRotation(rotation);
	m_body->SetTransform(b2Vec2(GetPosition().x, GetPosition().y), rotation);

	for (auto & compoenent : m_visual)
	{
		compoenent->SetRotation(rotation);
	}
}

float CGun::GetRotation() const
{
	return m_body->GetAngle();
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

	SetVisual();
	CreateBody(40.f, 15.f, 25.f);
}

void CGun::Advance(float dt)
{
	(void)dt;
	for (auto & component : m_visual)
	{
		component->SetRotation(GetRotation());
		component->SetReferenceSystemOrigin(GetReferenceSystemOrigin());
	}
}


void CGun::CheckParametres()
{
	CStaticShape::CheckParametres();

}

void CGun::CreateBody(float trunkWidth
					, float trunkHeigth
					, float baseRadius)
{
	const float byXShift = DEFAULT_BALL::RADIUSE + trunkHeigth * (0.5f) - DEFAULT_GUN::SHIFT_TRUNK;
	const float byYShift = -trunkHeigth / 2.f;
	CWall::AddRectangleToBody(m_body
							, SSize(trunkWidth, trunkHeigth) 
							, Convert::ToBox(glm::vec2(byXShift, byYShift)) );

	CBall::AddCircleToBody(m_body, baseRadius);
}


void CGun::SetVisual()
{
	std::shared_ptr<CCircleView> pCircle = std::make_shared<CCircleView>();

	pCircle->SetRadius(25.f);
	pCircle->SetPosition(glm::vec2());
	pCircle->SetOutlineColor(Colors::BLACK);
	pCircle->SetReferenceSystemOrigin(GetReferenceSystemOrigin());

	m_visual.push_back(std::move(pCircle));

	std::shared_ptr<CRectangleView> pTrunk = std::make_shared<CRectangleView>();

	pTrunk->SetHeight(15.f);
	pTrunk->SetWidth(40.f);
	pTrunk->SetPosition(glm::vec2(DEFAULT_BALL::RADIUSE + pTrunk->GetHeight() - DEFAULT_GUN::SHIFT_TRUNK
									, -pTrunk->GetHeight() / 2.f));
	pTrunk->SetOrigin(glm::vec2(-pTrunk->GetPosition().x
					, pTrunk->GetHeight() / 2.f));

	pTrunk->SetOutlineColor(Colors::BLACK);
	pTrunk->SetReferenceSystemOrigin(GetReferenceSystemOrigin());

	m_visual.push_back(std::move(pTrunk));

}