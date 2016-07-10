#include "stdafx.h"
#include "StaticShape.h"

CStaticShape::CStaticShape() 
	: IStaticShape()
	, CDrawable()
{
	m_defBody.type = b2_staticBody;

	m_defBody.position.x = NONE_VALUE::FLOAT;
	m_defBody.position.y = NONE_VALUE::FLOAT;

	//m_defBody.angle = NONE_VALUE::FLOAT; // TODO : see need define this

	m_referenceSystemOrigin = NONE_VALUE::GLM_VEC2;
	//m_shapeOrigin = NONE_VALUE::GLM_VEC2; // TODO : see need define this

}

void CStaticShape::SetPosition(const glm::vec2 & position)
{
	m_defBody.position.Set(Convert::ToBox(position.x), Convert::ToBox(position.y));
}

void CStaticShape::SetPosition(float x, float y)
{
	m_defBody.position.Set(Convert::ToBox(x), Convert::ToBox(y));
}

glm::vec2 CStaticShape::GetPosition() const
{
	return glm::vec2(Convert::ToNormal(m_body->GetPosition().x)
					, Convert::ToNormal(m_body->GetPosition().y) );
}

glm::vec2 CStaticShape::GetCenterPosition(const glm::vec2 & origin) const
{
	return GetPosition() + Convert::ToBox(origin);
}

glm::vec2 CStaticShape::GetCenterPosition() const
{
	return GetPosition() + GetReferenceSystemOrigin();
}

float CStaticShape::GetRotation() const
{
	if (m_body)
	{
		return m_body->GetAngle();
	}
	else
	{
		return m_defBody.angle;
	}
}

void CStaticShape::SetRotation(float rotation)
{
	if (!m_body)
	{
		m_defBody.angle = rotation;
	}
}

void CStaticShape::AddToWorld(b2World * world)
{
	m_body = world->CreateBody(&m_defBody);
}

void CStaticShape::CheckParametres()
{
	if ((m_defBody.position.x == NONE_VALUE::FLOAT)
		&&
		(m_defBody.position.y == NONE_VALUE::FLOAT))
	{
		throw std::runtime_error("Not define position!!!");
	}

	/*// TODO : see need define this
		if (m_defBody.angle == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define angle!!!");
	}

	*/

	if (m_referenceSystemOrigin == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define reference system origin!!!");
	}

	/* // TODO : see need define this
		if (m_shapeOrigin == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define shape origin!!!");
	}

	*/

}

