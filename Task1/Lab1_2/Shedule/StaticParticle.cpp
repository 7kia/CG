#include "stdafx.h"
#include "StaticParticle.h"

CStaticParticle::CStaticParticle()
	: CParticle()
{
}

void CStaticParticle::Advance(float dt)
{
	if (m_moveFunction != nullptr)
	{
		SetPosition(m_moveFunction->operator()(dt, GetPosition()) );
	}
	else
	{
		throw std::runtime_error("Not move function!!!");
	}
}

void CStaticParticle::SetMoveFunction(std::shared_ptr<MoveFunction> function)
{
	m_moveFunction = function;
}

void CStaticParticle::ApplyAcceleration(const glm::vec2 & acceleration)
{
	(void)acceleration;
}
