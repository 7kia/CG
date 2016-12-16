#include "stdafx.h"
#include "HaveLifeObject.h"

CHaveLifeObjects::CHaveLifeObjects()
	: CHaveWeaponTypes()
{
	SetTypeLifeObject(size_t(CLifeObjectType::Id::Player)
		, IdFaction::Player
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Player)]
		, 15.f
		, 5.f
		, 100
		, CWeaponType::Id::EnemyWeapon);// TODO : replace to PlayerWeapon

	SetTypeLifeObject(size_t(CLifeObjectType::Id::Enemy)
		, IdFaction::Enemy
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Player)]// TODO: add texture for enemy
		, 8.f
		, 15.f
		, 10
		, CWeaponType::Id::EnemyWeapon);
	
}


CLifeObjectType& CHaveLifeObjects::GetLifeObjectType(const CLifeObjectType::Id index)
{
	return m_lifeObjectsTypes[size_t(index)];
}

void CHaveLifeObjects::SetTypeLifeObject(size_t index
	, IdFaction idFaction
	, const std::string & textureName
	, const float velocity
	, const float visionRange
	, const int health
	, CWeaponType::Id idWeapon
	)
{
	//m_lifeObjectsTypes[index].SetId(index);
	m_lifeObjectsTypes[index].SetIdFaction(idFaction);
	m_lifeObjectsTypes[index].SetTexture(textureName);

	m_lifeObjectsTypes[index].SetVelocity(velocity);
	m_lifeObjectsTypes[index].SetVisionRange(visionRange);
	m_lifeObjectsTypes[index].SetHealth(health);
	m_lifeObjectsTypes[index].SetWeapon(m_weaponTypes[size_t(idWeapon)]);
}
