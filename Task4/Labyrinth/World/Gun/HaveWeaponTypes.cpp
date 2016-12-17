#include "stdafx.h"
#include "HaveWeaponTypes.h"
#include "World\World.h"


CHaveWeaponTypes::CHaveWeaponTypes()
	: CHaveShootTypes()
{
	SetWeaponType(CWeaponType::Id::PlayerWeapon
		, 25// damage
		, 1.f// timeReload
		, GetShootType(CShootType::Id::Player)
		, 9.f// velocity
		, 7.f// distanse
	);
	SetWeaponType(CWeaponType::Id::EnemyWeapon
		, 5// damage
		, 1.f// timeReload
		, GetShootType(CShootType::Id::Enemy)
		, 9.f// velocity
		, 7.f// distanse
	);
}

const CWeaponType * CHaveWeaponTypes::GetWeaponType(const CWeaponType::Id index) const
{
	return &m_weaponTypes[size_t(index)];
}

void CHaveWeaponTypes::SetWeaponType(CWeaponType::Id typeIndex
	, const int damage
	, const float timeReload
	, const CShootType & shootType
	, const float velocity
	, const float distanse
	)
{
	size_t index = size_t(typeIndex);
	m_weaponTypes[index].SetId(typeIndex);


	m_weaponTypes[index].SetDamage(damage);
	m_weaponTypes[index].SetTime(timeReload);
	m_weaponTypes[index].SetTypeShoot(shootType);// TODO : replace
	m_weaponTypes[index].SetVelocity(velocity);
	m_weaponTypes[index].SetDistanse(distanse);
}