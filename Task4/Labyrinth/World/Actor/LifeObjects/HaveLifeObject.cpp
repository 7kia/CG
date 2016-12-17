#include "stdafx.h"
#include "HaveLifeObject.h"

CHaveLifeObjects::CHaveLifeObjects()
	: CHaveWeaponTypes()
{
	SetTypeLifeObject(CLifeObjectType::Id::Player
		, IdFaction::Player
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Player)]
		, 3.f// velocity
		, 5.f// visionRange
		, 100// health
		, CWeaponType::Id::EnemyWeapon);// TODO : replace to PlayerWeapon

	SetTypeLifeObject(CLifeObjectType::Id::Enemy
		, IdFaction::Enemy
		, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Player)]// TODO: add texture for enemy
		, 2.f// velocity
		, 12.f// visionRange
		, 10// health
		, CWeaponType::Id::EnemyWeapon);
	
}


CLifeObjectType& CHaveLifeObjects::GetLifeObjectType(const CLifeObjectType::Id index)
{
	return m_lifeObjectsTypes[size_t(index)];
}

void CHaveLifeObjects::SetTypeLifeObject(CLifeObjectType::Id typeIndex
	, IdFaction idFaction
	, const std::string & textureName
	, const float velocity
	, const float visionRange
	, const int health
	, CWeaponType::Id idWeapon
	)
{
	size_t index = size_t(typeIndex);
	m_lifeObjectsTypes[index].SetId(typeIndex);

	m_lifeObjectsTypes[index].SetIdFaction(idFaction);
	m_lifeObjectsTypes[index].SetTexture(textureName);

	m_lifeObjectsTypes[index].SetVelocity(velocity);
	m_lifeObjectsTypes[index].SetVisionRange(visionRange);
	m_lifeObjectsTypes[index].SetHealth(health);
	m_lifeObjectsTypes[index].SetWeapon(m_weaponTypes[size_t(idWeapon)]);
}
