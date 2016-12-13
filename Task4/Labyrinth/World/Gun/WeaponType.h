#pragma once

#include "World\Actor\Shoot\Shoot.h"
#include "World\Actor\HaveDamage.h"


namespace WeaponTypeSpace
{
	enum class Id
	{
		Player = 0
		, Enemy
		, AmountTypes
	};


	const unsigned AMOUNT_TYPES = unsigned(Id::AmountTypes);


};

class CWeaponType : public CHaveDamage
{
public:
	CWeaponType();
public:
	enum class Id
	{
		NONE = -1,
		PlayerWeapon = 0,
		EnemyWeapon,
		AmountIDs
	};

	void					SetTime(float time);
	float					GetTime() const;

	void					SetVelocity(float setVelocity);
	float					GetVelocity() const;

	void					SetTypeShoot(const CShootType &type);
	const CShootType&		GetTypeShoot() const;

	void					SetDistanse(float distance);
	float					GetDistance() const;

private:

	float					m_time;
	float					m_velocity;
	float					m_distance;
	const CShootType*		m_type_shoot;
};