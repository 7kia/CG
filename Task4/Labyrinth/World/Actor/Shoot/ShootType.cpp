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


void CShootType::SetId(Id id)
{
	m_id = id;
}

CShootType::Id CShootType::GetId() const
{
	return m_id;
}
