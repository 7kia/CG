#include "stdafx.h"
#include "DynamicShape.h"

CDynamicBody::CDynamicBody()
	: IHaveVelocity()
	, CStaticShape()
{
	m_defBody.type = b2_dynamicBody;

	m_defBody.linearVelocity.x = NONE_VALUE::FLOAT;
	m_defBody.linearVelocity.y = NONE_VALUE::FLOAT;
}

void CDynamicBody::Advance(float dt)
{
	(void)dt;
}

glm::vec2 CDynamicBody::GetVelocity() const
{
	return glm::vec2(Convert::ToNormal(m_defBody.linearVelocity.x)
					, Convert::ToNormal(m_defBody.linearVelocity.x) );
}

void CDynamicBody::SetVelocity(const glm::vec2 & value)
{
	m_defBody.linearVelocity.x = Convert::ToBox(value.x);
	m_defBody.linearVelocity.y = Convert::ToBox(value.y);
}

void CDynamicBody::ApplyAcceleration(const glm::vec2 & acceleration)
{
	const glm::vec2 convertAcceleration = Convert::ToBox(acceleration);
	m_body->ApplyForceToCenter(b2Vec2(convertAcceleration.x, convertAcceleration.y), true);// TODO : what is wake?
}

void CDynamicBody::CheckParametres()
{
	if ((m_defBody.linearVelocity.x == NONE_VALUE::FLOAT)
		&& (m_defBody.linearVelocity.y == NONE_VALUE::FLOAT))
	{
		throw std::runtime_error("Undefined velocity");
	}
}
