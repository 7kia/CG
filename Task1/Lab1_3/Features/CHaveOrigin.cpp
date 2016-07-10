#include "stdafx.h"
#include "CHaveOrigin.h"

CHaveOrigin::CHaveOrigin()
	: IHaveOrigin()
{
}

void CHaveOrigin::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	m_referenceSystemOrigin = Convert::ToBox(origin);
}

glm::vec2 CHaveOrigin::GetReferenceSystemOrigin() const
{
	return Convert::ToNormal(m_referenceSystemOrigin);
}

void CHaveOrigin::SetOrigin(const glm::vec2 & origin)
{
	m_shapeOrigin = Convert::ToBox(origin);
}

glm::vec2 CHaveOrigin::GetOrigin() const
{
	return Convert::ToNormal(m_shapeOrigin);
}

CHavePositionAndOrigin::CHavePositionAndOrigin()
	: CHaveOrigin()
{
}

glm::vec2 CHavePositionAndOrigin::GetCenterPosition(const glm::vec2 & origin) const
{
	return GetPosition() + origin;
}

glm::vec2 CHavePositionAndOrigin::GetCenterPosition() const
{
	return GetPosition() + Convert::ToNormal(m_referenceSystemOrigin);
}