#include "stdafx.h"
#include "CHaveOrigin.h"

CHaveOrigin::CHaveOrigin()
	: IHaveOrigin()
{
}

void CHaveOrigin::SetReferenceSystemOrigin(const glm::vec2 & origin)
{
	m_referenceSystemOrigin = ConvertToBoxCoordinates(origin);
}

glm::vec2 CHaveOrigin::GetReferenceSystemOrigin() const
{
	return ConvertToNormalCoordinates(m_referenceSystemOrigin);
}

void CHaveOrigin::SetOrigin(const glm::vec2 & origin)
{
	m_shapeOrigin = ConvertToBoxCoordinates(origin);
}

glm::vec2 CHaveOrigin::GetOrigin() const
{
	return ConvertToNormalCoordinates(m_shapeOrigin);
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
	return GetPosition() + ConvertToNormalCoordinates(m_referenceSystemOrigin);
}