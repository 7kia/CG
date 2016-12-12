#pragma once

#include "../Entity/VisualDataType.h"
#include "../Entity/SoundDataType.h"
#include "../Entity/HaveDeathEffect.h"


#include "../Entity/Entity.h"
#include "../Entity/Collision.h"
#include "../Entity/Features.h"
#include "../Entity/Weapon.h"
#include "../HealthBar/HealthBar.h"
#include "../Effect/Effect.h"

struct SRange
{
	SRange();
	SRange(float start, float end);

	bool IsBetween(float value) const;
	float	start = 0;
	float	end = 0;
};

static const std::vector<SRange> rangesDirections = {	SRange(-22.5f, 22.5f)
													,	SRange(22.6f, 67.5f)
													,	SRange(67.6f, 112.5f)
													,	SRange(112.6f, 157.5f)
													,	SRange(157.6f, 202.5f)
													,	SRange(-157.5f, -112.6f)
													,	SRange(-112.5f, -67.6f)
													,	SRange(-67.5f, -22.6f) };

class TypeLifeObject :
	public CVisualDataType
	, public CSoundDataType
	, public CHaveDeathEffect
{
public:
	~TypeLifeObject();
public:

	enum ID
	{
			None = -1
		,	Player
		,	Zergling
		,	Hydralisk
		,	AmountIDs
	};

	void					SetVelocity(float setVelocity);
	float					GetVelocity() const;

	void					SetHealth(int value);
	int						GetHealth() const;

	void					SetVisionRange(float range);
	float					GetVisionRange() const;

	int						GetDamage();

	void					SetWeapon(const CTypeWeapon& weapon);
	const CTypeWeapon&		GetTypeWeapon() const;

	void							SetMoveAnimations(const CollectionAnimations & animations);
	const CollectionAnimations &	GetAnimationsMove() const;

	void							SetAttackAnimations(const CollectionAnimations & animations);
	const CollectionAnimations &	GetAttackAnimations() const;

	void							SetId(ID id);
	ID								GetId() const;

	// TODO : there not enough functional
private:
	float							m_velocity = 0.f;
	float							m_visionRange = 0.f;

	CDynamicFeature					m_health;
	const CTypeWeapon*				m_weapon;

	CollectionAnimations			m_moveAnimations;
	CollectionAnimations			m_attackAnimations;

	ID								m_id = ID::None;
};
