#pragma once

#include "Mixin/Material/HaveTexture.h"

#include "World/Actor/Features.h"
#include "World/Gun/Weapon.h"

struct SRange
{
	SRange();
	SRange(float start, float end);

	bool IsBetween(float value) const;
	float	start = 0;
	float	end = 0;
};



class CLifeObjectType : public CHaveTexture
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

	void					SetHealth(int value);
	int						GetHealth() const;

	void					SetMaxHealth(int value);
	int						GetMaxHealth() const;


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

	CDynamicFeature					m_health;
	const CWeaponType*				m_weapon;


	Id								m_id = Id::None;
};
