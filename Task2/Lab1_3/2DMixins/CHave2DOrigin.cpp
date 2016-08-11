#include "stdafx.h"
#include "CHave2DOrigin.h"

CHave2DOrigin::CHave2DOrigin()
	: IHave2DOrigin()
{
}

void CHave2DOrigin::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	m_referenceSystemOrigin = Convert::ToBox(origin);
}

glm::vec2 CHave2DOrigin::GetReferenceSystemOrigin() const
{
	return Convert::ToNormal(m_referenceSystemOrigin);
}

void CHave2DOrigin::SetOrigin(const glm::vec2 & origin)
{
	m_shapeOrigin = Convert::ToBox(origin);
}

glm::vec2 CHave2DOrigin::GetOrigin() const
{
	return Convert::ToNormal(m_shapeOrigin);
}

CHavePositionAndOrigin::CHavePositionAndOrigin()
	: CHave2DOrigin()
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