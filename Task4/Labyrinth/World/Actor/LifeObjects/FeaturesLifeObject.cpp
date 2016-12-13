#include "stdafx.h"
#include "World\World.h"
#include "LifeObjects.h"

void CLifeObject::SetState(StateId state)
{
	m_state = state;

	if (m_state != StateId::Attack)
	{
		m_weapon.SetState(CWeapon::IdState::NotActive);
	}
}

CLifeObject::StateId CLifeObject::GetState() const
{
	return m_state;
}

float CLifeObject::GetVisionRange() const
{
	return m_type->GetVisionRange();
}

int CLifeObject::GetDamage()
{
	return m_weapon.GetDamage();
}

void CLifeObject::SetTypeWeapon(const CWeaponType & weapon)
{
	m_weapon.SetType(weapon);
}

const CWeapon & CLifeObject::GetWeapon() const
{
	return m_weapon;
}



CLifeObjectType::Id CLifeObject::GetIdType() const
{
	return m_type->GetId();
}

const CLifeObjectType & CLifeObject::GetType() const
{
	return *m_type;
}

float CLifeObject::GetDistanceWeapon() const
{
	return m_weapon.GetDistance();
}
