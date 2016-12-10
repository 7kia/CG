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

void CHaveLinearVelocity::SetMaxSpeedUpTime(float time)
{
	m_maxSpeedUpTime = time;
}

float CHaveLinearVelocity::GetMaxSpeedUpTime() const
{
	return m_maxSpeedUpTime;
}

void CHaveLinearVelocity::SetMinSpeedUpTime(float time)
{
	m_minSpeedUpTime = time;
}

float CHaveLinearVelocity::GetMinSpeedUpTime() const
{
	return m_minSpeedUpTime;
}

float CHaveLinearVelocity::GetCurrentLinearVelocity(float deltaTime)
{
	if (m_directionWalk != DirectionWalk::None)
	{
		m_currentSpeedUpTime += deltaTime;

		if (m_currentSpeedUpTime >= m_maxSpeedUpTime)
		{
			m_currentVelocity = m_maxLinearVelocity;
		}
		else if ((m_currentSpeedUpTime > m_minSpeedUpTime) && (m_currentSpeedUpTime < m_maxSpeedUpTime))
		{
			m_currentVelocity = m_maxLinearVelocity / m_maxSpeedUpTime * m_currentSpeedUpTime;
		}

		if (m_currentSpeedUpTime > m_minSpeedUpTime)
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
		m_currentSpeedUpTime = 0.f;
	}
}
