#include "stdafx.h"
#include "HaveRotationSpeed.h"

CHaveRotationSpeed::CHaveRotationSpeed(float rotation)
	: IHaveRotationSpeed()
	, m_rotationSpeed(rotation)
{
}

void CHaveRotationSpeed::SetRotationSpeed(float rotation)
{
	m_rotationSpeed = rotation;
}

float CHaveRotationSpeed::GetRotationSpeed() const
{
	return m_rotationSpeed;
}

void CHaveRotationSpeed::SetCurrentRotationSpeed(float rotation)
{
	m_currentRotation = rotation;
}

float CHaveRotationSpeed::GetCurrentRotationSpeed() const
{
	return m_currentRotation;
}

void CHaveRotationSpeed::ResetCurrentRotationSpeed()
{
	m_currentRotation = 0.f;
}
