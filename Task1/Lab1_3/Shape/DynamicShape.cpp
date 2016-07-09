#include "stdafx.h"
#include "DynamicShape.h"

CDynamicBody::CDynamicBody(b2World * world)
	: IHaveVelocity()
	, CStaticShape(world)
{
	m_defBody.type = b2_dynamicBody;

	m_defBody.linearVelocity.x = NONE_VALUE::FLOAT;
	m_defBody.linearVelocity.y = NONE_VALUE::FLOAT;
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
	//ApplyAcceleration(ConvertToBoxCoordinates(value));
}

void CDynamicBody::ApplyAcceleration(const glm::vec2 & acceleration)
{
	const glm::vec2 convertAcceleration = ConvertToBoxCoordinates(acceleration);
	m_body->ApplyForceToCenter(b2Vec2(convertAcceleration.x, convertAcceleration.y), true);// TODO : what is wake?
}

void CDynamicBody::CheckParametres()
{
	if ((m_defBody.linearVelocity.x == NONE_VALUE::FLOAT)
		&&
		(m_defBody.linearVelocity.y == NONE_VALUE::FLOAT))
	{
		throw std::runtime_error("Not define velocity!!!");
	}
}
