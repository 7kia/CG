#include "stdafx.h"
#include "HaveLinearVelocity.h"

CHaveLinearVelocity::CHaveLinearVelocity(float velocity)
	: IHaveLinearVelocity()
	, m_linearVelocity(velocity)
{
}

void CHaveLinearVelocity::SetLinearVelocity(float velocity)
{
	m_linearVelocity = velocity;
}

float CHaveLinearVelocity::GetLinearVelocity() const
{
	return m_linearVelocity;
}

void CHaveLinearVelocity::SetCurrentLinearVelocity(float velocity)
{
	m_currentVelocity = velocity;
}

float CHaveLinearVelocity::GetCurrentLinearVelocity() const
{
	return m_currentVelocity;
}

void CHaveLinearVelocity::ResetCurrentLinearVelocity()
{
	m_currentVelocity = 0.f;
}
