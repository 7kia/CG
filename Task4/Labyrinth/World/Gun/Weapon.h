#pragma once

#include "WeaponType.h"

class CWeapon
{
public:
	enum class IdState
	{
		NotActive = 0	,
		NotShoot		,
		Shoot
	};

	void					SetType(const CWeaponType& type);
	const CWeaponType&		GetType() const;

	int						GetDamage() const;
	float					GetVelocity() const;

	void					Update(float dt);
	void					SetState(IdState state);
	IdState					GetState() const;

	float					GetDistance() const;
	void					ResetTimer();

	const CShootType&		GetTypeShoot() const;

private:
	IdState					m_state = IdState::NotActive;
	float					m_time = 0.f;

	CDynamicFeature			m_damage;
	const CWeaponType*		m_type;
};