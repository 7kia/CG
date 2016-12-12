#pragma once

#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <array>

#include "World/Actor.h"
#include "Mixin/HaveLinearVelocity.h"
#include "Mixin/HaveRotationSpeed.h"
#include "Mixin/HaveDirection.h"
#include "Mixin/Drawable.h"
#include "Mixin/Material/HaveTexture.h"

#include "2DShape/2DCircleCollision.h"
#include "3DShape\3DSphere.h"

#include "Lights.h"
#include "Camera\Cameras.h"
#include "DispatchEvent.h"

#include "World/Features.h"
#include "World\Gun\Weapon.h"

#include "TypesLifeObjects.h"// TODO

class CWorld;

// TOOD : CMovement transfer to Behaveour
class CLifeObject
	: public IActor
	, public CHave3DPosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
	, public CHaveTexture
{
public:
	// LifeObjects.cpp
	CLifeObject();
	explicit CLifeObject(const glm::vec3 & position
		, const glm::vec3 & direction
		, const std::string & texturePath
		, CWorld* pWorld);

public:
	enum class StateId
	{
			NotActive = 0
		,	Move
		,	Attack
	};

//////////////////////////////////////////////////////////////////////
// Methods
public:
	void				SetState(StateId state);
	StateId				GetState() const;

	//--------------------------------------------
	// IActor
	void				Update(float deltaTime) override;
	void				Draw() const override;
	//--------------------------------------------

	void				SetType(TypeLifeObject &setType);

	void				SetCollison(CWorld* pWorld);

	/////////////////
	// UpdateLifeObject.cpp
	virtual void			UpdatePosition(float dt);

	void					SetAnimationMove();
	void					SetAttackAnimation();

	void					ResetWeapon();
	/////////////////

	/////////////////
	// FeaturesLifeObject.cpp
	void				SetHealth(int value);
	void				AddHealth(int value);

	int					GetHealth();
	int					GetMaxHealth();

	float				GetVisionRange() const;

	int					GetDamage();

	void				SetTypeWeapon(const CTypeWeapon& weapon);
	const CWeapon&		GetWeapon() const;

	//void				SetHealthBar(const CBar &bar);
	//CBar &				GetHealthBar();

	float				GetDistanceWeapon() const;

	TypeLifeObject::ID			GetIdType() const;// TODO : see need it
	const TypeLifeObject&		GetType() const;
	/////////////////

	/////////////////
	// -.cpp
	// \/ class CWeapon
	void							Shoot();

	/////////////////
	void					Attack();
	void					SetWeaponState(CWeapon::IdState state);
	CWeapon::IdState		GetWeaponState() const;

	void					SetWeapon(const CTypeWeapon & typeWeapon);
	/////////////////
public:

	////////
	// TODO : transfer to CWeapon
	float m_timerAttack = 0.f;
	float m_timeReload = 0.05f;
	///////

protected:
	std::shared_ptr<const TypeLifeObject>					m_type;//TypeLifeObject

	C2DCircleCollision				m_collision;
	CIdentity3DSphere				m_visual;

	CWorld*							m_world = nullptr;// For create shoot
	CWeapon							m_weapon;

	CDynamicFeature					m_health;

	StateId							m_state = StateId::NotActive;
	// TODO : delete
};

