#include "stdafx.h"
#include "Gun.h"

CGun::CGun()
	: CStaticShape()
{
	auto pCircle = std::make_shared<CBall>();
	m_components.push_back(pCircle);

	auto pTrunk = std::make_shared<CRectangle>();
	pTrunk->SetWidth(15.f);
	pTrunk->SetHeight(20.f);
	pTrunk->SetPosition(-glm::vec2(7.5f, DEFAULT_BALL::RADIUSE + pTrunk->GetHeight() - DEFAULT_GUN::SHIFT_TRUNK));

	m_components.push_back(pTrunk);
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
	return false;
}

void CGun::SetPosition(const glm::vec2 & position)
{
	CHavePosition::SetPosition(position);

	for (auto & component : m_components)
	{
		component->SetOrigin(position + m_origin);
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
	return GetPosition() + m_origin;
}

void CGun::SetOrigin(const glm::vec2 & origin)
{
	CHavePosition::SetOrigin(origin);

	for (auto & component : m_components)
	{
		component->SetOrigin(origin);
	}
}
