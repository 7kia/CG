#pragma once

#include "Mixin/Material/HaveTexture.h"

#include "World/Actor/HaveHealth.h"
#include "World/Actor/IsDeletable.h"
#include "World/Actor/Faction.h"
#include "World/Gun/Weapon.h"

struct SRange
{
	SRange();
	SRange(float start, float end);

	bool IsBetween(float value) const;
	float	start = 0;
	float	end = 0;
};



class CLifeObjectType 
	: public CHaveTexture
	, public CHaveFaction
{
public:
	CLifeObjectType();
public:

	enum Id
	{
			None = -1
		,	Player
		,	Enemy
		,	AmountIDs
	};

	void					SetVelocity(float setVelocity);
	float					GetVelocity() const;

	void					SetHealth(int value);// TOOD : see can it mix
	int						GetHealth() const;

	void					SetVisionRange(float range);
	float					GetVisionRange() const;

	int						GetDamage();

	void					SetWeapon(const CWeaponType& weapon);
	const CWeaponType&		GetTypeWeapon() const;


	void							SetId(Id id);
	Id								GetId() const;

	// TODO : there not enough functional
private:
	float							m_velocity = 0.f;
	float							m_visionRange = 0.f;

	CStaticFeature					m_health;
	const CWeaponType*				m_weapon;


	Id								m_id = Id::None;
};
