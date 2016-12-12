#include "stdafx.h"
#include "HaveWeaponTypes.h"
#include "World\World.h"

using namespace WeaponTypeSpace;


CHaveWeaponTypes::CHaveWeaponTypes()
	: CHaveShootTypes()
{
	SetWeaponType(size_t(WeaponTypeSpace::Id::Player)
		, 25
		, 1.f
		, GetShootType(ShootTypeSpace::Id::Player)
		, 15.f
		, 5.f);
	SetWeaponType(size_t(WeaponTypeSpace::Id::Enemy)
		, 5
		, 1.f
		, GetShootType(ShootTypeSpace::Id::Enemy)
		, 15.f
		, 5.f);
}

const CWeaponType * CHaveWeaponTypes::GetWeaponType(const WeaponTypeSpace::Id index) const
{
	return &m_weaponTypes[size_t(index)];
}

void CHaveWeaponTypes::SetWeaponType(size_t index
	, const int damage
	, const float timeReload
	, const CShootType & shootType
	, const float velocity
	, const float distanse
	)
{
	m_weaponTypes[index].SetDamage(damage);
	m_weaponTypes[index].SetTime(timeReload);
	m_weaponTypes[index].SetTypeShoot(shootType);// TODO : replace
	m_weaponTypes[index].SetVelocity(velocity);
	m_weaponTypes[index].SetDistanse(distanse);
}