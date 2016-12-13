#include "stdafx.h"
#include "Shoot.h"
#include "../World.h"
#include "World\Gun\Weapon.h"

CShoot::CShoot()
	: IActor()
	, CHave3DPosition()
	, CHaveDirection(ShootSpace::PLAYER_DIRECTION)
	, CHaveLinearVelocity(ShootSpace::LINEAR_MOVE_SPEED)
	, m_collision(1.f, glm::vec2())
{
}


CShoot::CShoot(const glm::vec3 & position
				, const glm::vec3 & direction
				, const CWeapon & weapon
				, CWorld* pWorld)

	: IActor()
	, CHave3DPosition(position)
	, CHaveDirection(direction)
	, CHaveLinearVelocity(weapon.GetType().GetVelocity())// TODO : fix to type
	, m_collision(1.f, glm::vec2())
{
	m_damage.SetValue(weapon.GetType().GetDamage());

	SetCollison(pWorld);
	SetType(weapon.GetTypeShoot());
}

void CShoot::Update(float deltaTime)
{
	//m_collision.ResetVelocity();
	auto collisionPosition = m_collision.GetPosition();
	auto position = glm::vec3(collisionPosition.x, 0.f, collisionPosition.y);

	const float velocity = GetMaxLinearVelocity();
	auto direction = GetDirection();

	auto linearVelocity = deltaTime * direction * velocity;
	m_collision.SetVelocity(glm::vec2(linearVelocity.x, linearVelocity.z));

	m_visual.SetTransform(glm::translate(glm::mat4(), position));
	m_collision.Advance(deltaTime);
}

void CShoot::Draw() const
{
	GetType().GetTexture()->DoWhileBinded([&] {
		m_visual.Draw();
	});
}

void CShoot::SetCollison(CWorld* pWorld)
{
	m_collision.SetRadius(ShootSpace::RADIUS);// TODO : fix radius
	m_collision.SetReferenceSystemOrigin(glm::vec2());

	auto position = GetPosition();
	m_collision.SetPosition(position.x, position.y);
	m_collision.SetVelocity(glm::vec2());

	m_visual.SetTransform(glm::translate(glm::mat4(), position));

	m_collision.AddToWorld(pWorld->GetWorld());
}

void CShoot::SetType(const CShootType & type)
{
	m_visual.SetType(&type);
}

const CShootType & CShoot::GetType() const
{
	return *m_visual.GetType();
}
