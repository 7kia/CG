#include "stdafx.h"
#include "HaveDamage.h"

CHaveDamage::CHaveDamage()
{
}

void CHaveDamage::SetDamage(int value)
{
	m_damage.SetValue(value);
}

void CHaveDamage::AddDamage(int value)
{
	m_damage.AddToValue(value);
}


int CHaveDamage::GetDamage() const
{
	return m_damage.GetValue();
}

