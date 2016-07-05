#include "stdafx.h"
#include "StaticShape.h"

CStaticShape::CStaticShape() 
	: IStaticShape()
	, CShape()
{
	m_defBody.type = b2_staticBody;
}

void CStaticShape::SetPosition(const glm::vec2 & position)
{
	m_defBody.position.Set(ConvertToBoxCoordinates(position.x), ConvertToBoxCoordinates(position.y));
}

void CStaticShape::SetPosition(float x, float y)
{
	m_defBody.position.Set(ConvertToBoxCoordinates(x), ConvertToBoxCoordinates(y));
}

glm::vec2 CStaticShape::GetPosition() const
{
	return glm::vec2(ConvertToNormalCoordinates(m_defBody.position.x)
					, ConvertToNormalCoordinates(m_defBody.position.y));
}

glm::vec2 CStaticShape::GetCenterPosition(const glm::vec2 & origin) const
{
	return GetPosition() + ConvertToBoxCoordinates(origin);
}

glm::vec2 CStaticShape::GetCenterPosition() const
{
	return GetPosition() + GetReferenceSystemOrigin();
}

float CStaticShape::GetRotation() const
{
	return m_defBody.angle;
}

void CStaticShape::SetRotation(float rotation)
{
	m_defBody.angle = rotation;
}

