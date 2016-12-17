#pragma once

#include "World\Actor\Shoot\Shoot.h"
#include "World\Actor\HaveDamage.h"

class CWeaponType : public CHaveDamage
{
public:
	CWeaponType();

	enum class Id
	{
		None = -1,
		PlayerWeapon = 0,
		EnemyWeapon,
		AmountTypes
	};
//////////////////////////////////////////////////////////////////////
// Methods

public:
	

	void					SetTime(float time);
	float					GetTime() const;

	void					SetVelocity(float setVelocity);
	float					GetVelocity() const;

	void					SetTypeShoot(const CShootType &type);
	const CShootType&		GetTypeShoot() const;

	void					SetDistanse(float distance);
	float					GetDistance() const;

	void					SetId(Id id);
	Id						GetId() const;

//////////////////////////////////////////////////////////////////////
// Data
private:

	float					m_time;
	float					m_velocity;
	float					m_distance;
	const CShootType*		m_type_shoot;

	Id						m_id = Id::None;

};