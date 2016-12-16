#pragma once

#include "LifeObjects.h"
#include "World/Gun/HaveWeaponTypes.h"

class CHaveLifeObjects
	: public CHaveWeaponTypes
{
public:
	CHaveLifeObjects();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	using ArrayLifeObjectsTypes = std::array<CLifeObjectType, size_t(CLifeObjectType::AmountIDs)>;

	CLifeObjectType&				GetLifeObjectType(const CLifeObjectType::Id index);

	void							SetTypeLifeObject(size_t index
													, IdFaction idFaction
													, const std::string & textureName
													, const float velocity
													, const float visionRange
													, const int health
													, CWeaponType::Id idWeapon
													);
//////////////////////////////////////////////////////////////////////
// Data
public:
	ArrayLifeObjectsTypes						m_lifeObjectsTypes;
	std::vector<LifeObjectSharedPtr>			m_lifeObjects;// TODO : create ActorFactory
};