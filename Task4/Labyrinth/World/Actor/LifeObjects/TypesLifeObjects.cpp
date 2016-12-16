#include "stdafx.h"
#include "TypesLifeObjects.h"


CLifeObjectType::CLifeObjectType()
	: CHaveTexture()
	, CHaveFaction()
{
}

void CLifeObjectType::SetVelocity(float setVelocity)
{
	m_velocity = setVelocity;
}

float CLifeObjectType::GetVelocity() const
{
	return m_velocity;
}

void CLifeObjectType::SetHealth(int value)
{
	m_health.SetValue(value);
}

int CLifeObjectType::GetHealth() const
{
	return m_health.GetValue();
}

void CLifeObjectType::SetVisionRange(float range)
{
	m_visionRange = range;
}

float CLifeObjectType::GetVisionRange() const
{
	return m_visionRange;
}

int CLifeObjectType::GetDamage()
{
	return m_weapon->GetDamage();
}

void CLifeObjectType::SetWeapon(const CWeaponType & weapon)
{
	m_weapon = &weapon;
}

const CWeaponType & CLifeObjectType::GetTypeWeapon() const
{
	return *m_weapon;
}


void CLifeObjectType::SetId(Id id)
{
	m_id = id;
}

CLifeObjectType::Id CLifeObjectType::GetId() const
{
	return m_id;
}

SRange::SRange()
	: start(0.f)
	, end(0.f)
{
}

SRange::SRange(float start, float end)
	: start(start)
	, end(end)
{
}

bool SRange::IsBetween(float value) const
{
	return (start <= value) && (end >= value);
}
