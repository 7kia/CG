#include "stdafx.h"
#include "HaveRotationSpeed.h"

CHaveRotationSpeed::CHaveRotationSpeed(float rotation)
	: m_maxRotationSpeed(rotation)
{
}

void CHaveRotationSpeed::SetMaxRotationSpeed(float rotation)
{
	m_maxRotationSpeed = rotation;
}

float CHaveRotationSpeed::GetMaxRotationSpeed() const
{
	return m_maxRotationSpeed;
}

void CHaveRotationSpeed::SetMaxRotationUpTime(float time)
{
	m_maxRotationUpTime = time;
}

float CHaveRotationSpeed::GetMaxRotationUpTime() const
{
	return m_maxRotationUpTime;
}

void CHaveRotationSpeed::SetMinRotationUpTime(float time)
{
	m_minRotationUpTime = time;
}

float CHaveRotationSpeed::GetMinRotationUpTime() const
{
	return m_minRotationUpTime;
}

float CHaveRotationSpeed::GetCurrentRotationSpeed(float deltaTime)
{
	if (m_directionRotation != DirectionRotation::None)
	{
		m_currentRotationUpTime += deltaTime;

		if (m_currentRotationUpTime >= m_maxRotationUpTime)
		{
			m_currentRotation = m_maxRotationSpeed;
		}
		else if ((m_currentRotationUpTime > m_minRotationUpTime) && (m_currentRotationUpTime < m_maxRotationUpTime))
		{
			m_currentRotation = m_maxRotationSpeed / m_maxRotationUpTime * m_currentRotationUpTime;
		}

		if (m_currentRotationUpTime > m_minRotationUpTime)
		{
			switch (m_directionRotation)
			{
			case DirectionRotation::Left:
				return m_currentRotation;
			case DirectionRotation::Right:
				return -m_currentRotation;
			default:
				return 0.0f;
			}
		}

	}
	return 0.0f;
}

void CHaveRotationSpeed::ResetCurrentRotationSpeed()
{
	m_currentRotation = 0.f;
	if (m_directionRotation == DirectionRotation::None)
	{
		m_currentRotationUpTime = 0.f;
	}

}
