#include "stdafx.h"
#include "HaveHealth.h"

CHaveHealth::CHaveHealth()
	: IHavehealth()
{
}

void CHaveHealth::SetHealth(int value)
{
	m_health.SetValue(value);
}

void CHaveHealth::AddHealth(int value)
{
	m_health.AddToValue(value);
}

void CHaveHealth::SetMaxHealth(int value)
{
	m_health.SetMaxValue(value);
}

void CHaveHealth::AddToMaxHealth(int value)
{
	m_health.AddToMaxValue(value);
}

int CHaveHealth::GetHealth()
{
	return m_health.GetValue();
}

int CHaveHealth::GetMaxHealth()
{
	return m_health.GetMaxValue();
}


