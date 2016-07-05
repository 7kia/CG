#include "stdafx.h"
#include "DynamicShape.h"

CDynamicBody::CDynamicBody()
	: IHaveVelocity()
	, CStaticShape()
{
	m_defBody.type = b2_dynamicBody;
}

void CDynamicBody::Advance(float dt)
{
	(void)dt;
	//m_velocity += dt * m_acceleration;
	//SetPosition(m_velocity + GetPosition());

	// TODO : this work do Step()

	//m_velocity = glm::vec2();// TODO : see need reset this
	//m_acceleration = glm::vec2();
}

glm::vec2 CDynamicBody::GetVelocity() const
{
	return glm::vec2(ConvertToNormalCoordinates(m_defBody.linearVelocity.x)
					, ConvertToNormalCoordinates(m_defBody.linearVelocity.x) );
}

void CDynamicBody::SetVelocity(const glm::vec2 & value)
{
	m_defBody.linearVelocity.x = ConvertToBoxCoordinates(value.x);
	m_defBody.linearVelocity.y = ConvertToBoxCoordinates(value.y);
	ApplyAcceleration(ConvertToBoxCoordinates(value));
}

void CDynamicBody::ApplyAcceleration(const glm::vec2 & acceleration)
{
	const glm::vec2 convertAcceleration = ConvertToBoxCoordinates(acceleration);
	m_body->ApplyForceToCenter(b2Vec2(convertAcceleration.x, convertAcceleration.y), true);// TODO : what is wake?
}
