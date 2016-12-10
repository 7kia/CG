#include "stdafx.h"
#include "Weapon.h"

void CWeapon::SetType(const CWeaponType & type)
{
	m_type = &type;

	m_damage.SetValue(type.GetDamage());
}

const CWeaponType & CWeapon::GetType() const
{
	return *m_type;
}

int CWeapon::GetDamage() const
{
	return m_damage.GetValue();
}

float CWeapon::GetVelocity() const
{
	return m_type->GetVelocity();
}

void CWeapon::Update(float dt)
{
	switch (m_state)
	{
	case IdState::NotActive:
		m_time = 0.f;
		break;
	case IdState::NotShoot:
		m_time += dt;
		if (m_time > m_type->GetTime())
		{
			m_state = IdState::Shoot;
			m_time = 0.f;
		}
		break;
	case IdState::Shoot:
		m_state = IdState::NotActive;
		m_time = 0.f;
		break;
	default:
		break;
	}

}

void CWeapon::SetState(IdState state)
{
	m_state = state;
}

CWeapon::IdState CWeapon::GetState() const
{
	return m_state;
}

float CWeapon::GetDistance() const
{
	return m_type->GetDistance();
}

void CWeapon::ResetTimer()
{
	m_time = 0.f;
}

const CShootType & CWeapon::GetTypeShoot() const
{
	return m_type->GetTypeShoot();
}
