#include "stdafx.h"
#include "World\World.h"
#include "LifeObjects.h"

CLifeObject::CLifeObject()
	: CActor(CActor::IdClass::LifeObject)
	, CHave3DPosition()
	, CHaveDirection()
	, CHaveLinearVelocity(LifeObjectSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(LifeObjectSpace::ROTATION_SPEED_RADIANS)
	, CHaveHealth()
	, m_visual(16, 16)
{

}


CLifeObject::CLifeObject(CLifeObjectType & type
						, CWorld* pWorld
						, const glm::vec3 & position
						, const glm::vec3 & direction)
	: CActor(CActor::IdClass::LifeObject)
	, CHave3DPosition(position)
	, CHaveDirection(direction)
	, CHaveLinearVelocity(LifeObjectSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(LifeObjectSpace::ROTATION_SPEED_RADIANS)
	, CHaveHealth()
	, m_visual(16, 16)

{
	SetType(type);
	SetCollison(pWorld);
}


void CLifeObject::SetType(CLifeObjectType & setType)
{
	m_type = &setType;
	//m_type = &setType;
	SetMaxLinearVelocity(m_type->GetVelocity());

	m_health.SetValue(m_type->GetHealth());
	m_health.SetMaxValue(m_type->GetHealth());

	m_weapon.SetType(m_type->GetTypeWeapon());

}

void CLifeObject::SetCollison(CWorld* pWorld)
{
	m_world = pWorld;

	m_collision.SetRadius(1.f);
	m_collision.SetReferenceSystemOrigin(glm::vec2());

	auto position = GetPosition();
	m_collision.SetPosition(position.x, position.y);
	m_collision.SetVelocity(glm::vec2());

	m_visual.SetTransform(glm::translate(glm::mat4(), position));

	m_collision.AddToWorld(pWorld->GetWorld());
	m_collision.SetMaster(this);
}

void CLifeObject::Attack()
{
	if (m_weapon.GetState() == CWeapon::IdState::NotActive)
	{
		m_weapon.SetState(CWeapon::IdState::NotShoot);
		
	}
}

void CLifeObject::SetWeaponState(CWeapon::IdState state)
{
	m_weapon.SetState(state);
}

CWeapon::IdState CLifeObject::GetWeaponState() const
{
	return m_weapon.GetState();
}

void CLifeObject::SetWeapon(const CWeaponType & typeWeapon)
{
	m_weapon.SetType(typeWeapon);
}

void CLifeObject::CheckHealth()
{
	if (GetHealth() <= 0)
	{
		SetStateLive(false);
	}
}
