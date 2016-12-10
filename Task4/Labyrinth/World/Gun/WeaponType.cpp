#include "stdafx.h"
#include "WeaponType.h"

using namespace std;

void CWeaponType::SetTime(float time)
{
	m_time = time;
}

float CWeaponType::GetTime() const
{
	return m_time;
}

void CWeaponType::SetVelocity(float setVelocity)
{
	m_velocity = setVelocity;
}

float CWeaponType::GetVelocity() const
{
	return m_velocity;
}

void CWeaponType::SetDamage(int value)
{
	m_damage.SetValue(value);
}

int CWeaponType::GetDamage() const
{
	return m_damage.GetValue();
}

void CWeaponType::SetTypeShoot(const CShootType & type)
{
	m_type_shoot = &type;
}

const CShootType& CWeaponType::GetTypeShoot() const
{
	return *m_type_shoot;
}

void CWeaponType::SetDistanse(float distance)
{
	m_distance = distance;
}

float CWeaponType::GetDistance() const
{
	return m_distance;
}


