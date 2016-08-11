#include "stdafx.h"
#include "Static2DShape.h"

CStatic2DShape::CStatic2DShape() 
	: IStatic2DShape()
	, CHave2DOrigin()
{
	m_defBody.type = b2_staticBody;

	m_defBody.position.x = NONE_VALUE::FLOAT;
	m_defBody.position.y = NONE_VALUE::FLOAT;

	//m_defBody.angle = NONE_VALUE::FLOAT; // TODO : see need define this

	m_referenceSystemOrigin = NONE_VALUE::GLM_VEC2;
	//m_shapeOrigin = NONE_VALUE::GLM_VEC2; // TODO : see need define this

}

void CStatic2DShape::SetPosition(const glm::vec2 & position)
{
	m_defBody.position.Set(Convert::ToBox(position.x), Convert::ToBox(position.y));
}

void CStatic2DShape::SetPosition(float x, float y)
{
	m_defBody.position.Set(Convert::ToBox(x), Convert::ToBox(y));
}

glm::vec2 CStatic2DShape::GetPosition() const
{
	return glm::vec2(Convert::ToNormal(m_body->GetPosition().x)
					, Convert::ToNormal(m_body->GetPosition().y) );
}

glm::vec2 CStatic2DShape::GetCenterPosition(const glm::vec2 & origin) const
{
	return GetPosition() + Convert::ToBox(origin);
}

glm::vec2 CStatic2DShape::GetCenterPosition() const
{
	return GetPosition() + GetReferenceSystemOrigin();
}

float CStatic2DShape::GetRotation() const
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

void CStatic2DShape::SetRotation(float rotation)
{
	if (!m_body)
	{
		m_defBody.angle = rotation;
	}
}

void CStatic2DShape::AddToWorld(b2World * world)
{
	m_body = world->CreateBody(&m_defBody);
}

void CStatic2DShape::CheckParametres()
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

