#include "stdafx.h"
#include "Dynamic2DShape.h"

CDynamicBody::CDynamicBody()
	: IHave2DVelocity()
	, CStatic2DShape()
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
	const glm::vec2 convertAcceleration = Convert::ToBox(acceleration);//, true
	m_body->ApplyForceToCenter(b2Vec2(convertAcceleration.x, convertAcceleration.y));// TODO : what is wake?
}

void CDynamicBody::ReserVelocity()
{
	//m_body->SetTransform(0.f);
	//m_body->S
	//if(GetVelocity())
	//m_body->ApplyForceToCenter(-m_body->GetLinearVelocity());
}

void CDynamicBody::CheckParametres()
{
	if ((m_defBody.linearVelocity.x == NONE_VALUE::FLOAT)
		&& (m_defBody.linearVelocity.y == NONE_VALUE::FLOAT))
	{
		throw std::runtime_error("Undefined velocity");
	}
}
