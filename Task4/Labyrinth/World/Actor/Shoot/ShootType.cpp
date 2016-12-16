#include "stdafx.h"
#include "ShootType.h"

CShootType::CShootType()
	: CHaveTexture()
	, CHaveFaction()
{
}

void CShootType::SetHealth(int value)
{
	m_health.SetValue(value);
}

int CShootType::GetHealth() const
{
	return m_health.GetValue();
}
