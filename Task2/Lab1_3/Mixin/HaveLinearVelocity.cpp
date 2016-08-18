#include "stdafx.h"
#include "HaveLinearVelocity.h"

CHaveLinearVelocity::CHaveLinearVelocity(float velocity)
	: m_maxLinearVelocity(velocity)
{
}

void CHaveLinearVelocity::SetMaxLinearVelocity(float velocity)
{
	m_maxLinearVelocity = velocity;
}

float CHaveLinearVelocity::GetMaxLinearVelocity() const
{
	return m_maxLinearVelocity;
}

void CHaveLinearVelocity::SetMaxTime(float time)
{
	m_maxTime = time;
}

float CHaveLinearVelocity::GetMaxTime() const
{
	return m_maxTime;
}

void CHaveLinearVelocity::SetMinTime(float time)
{
	m_minTime = time;
}

float CHaveLinearVelocity::GetMinTime() const
{
	return m_minTime;
}

float CHaveLinearVelocity::GetCurrentLinearVelocity(float deltaTime)
{
	if (m_directionWalk != DirectionWalk::None)
	{
		m_currentTime += deltaTime;

		if (m_currentTime >= m_maxTime)
		{
			m_currentVelocity = m_maxLinearVelocity;
		}
		else if ((m_currentTime > m_minTime) && (m_currentTime < m_maxTime))
		{
			m_currentVelocity = m_maxLinearVelocity / m_maxTime * m_currentTime;
		}

		if (m_currentTime > m_minTime)
		{
			switch (m_directionWalk)
			{
			case DirectionWalk::Forward:
				return m_currentVelocity;
			case DirectionWalk::Back:
				return -m_currentVelocity;
			default:
				return 0.0f;
			}
		}
		
	}
	return 0.0f;
}

void CHaveLinearVelocity::ResetCurrentLinearVelocity()
{
	m_currentVelocity = 0.f;
	if (m_directionWalk == DirectionWalk::None)
	{
		m_currentTime = 0.f;
	}
	//m_directionWalk = DirectionWalk::None; // TODO : fix
}
