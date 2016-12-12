#include "stdafx.h"
#include "World/World.h"
#include "LifeObjects.h"

void CLifeObject::Draw() const
{
	m_type->GetTexture()->DoWhileBinded([&] {
		m_visual.Draw();
	});
}

void CLifeObject::Update(float dt)
{
	int idAnimation;
	switch (m_state)
	{
	case StateId::NotActive:
		//break;
	case StateId::Move:
		UpdatePosition(dt);
		break;
	case StateId::Attack:
		if (m_weapon.GetState() != CWeapon::IdState::NotShoot)
		{
			m_weapon.SetState(CWeapon::IdState::NotShoot);
		}
		m_weapon.Update(dt);
		//SetAttackAnimation();
		break;
	default:
		break;
	}

	//m_healthBar.update(dt);
}


void CLifeObject::UpdatePosition(float dt)
{
	/*
		if (m_direction != Vec2::ZERO)
	{
		SetAnimationMove();

		Vec2 resultVector = m_direction;

		resultVector *= m_velocity;
		resultVector *= dt;

		CVisual::Move(resultVector);
		m_direction = Vec2::ZERO;

	}

	*/

	m_collision.ResetVelocity();
	auto collisionPosition = m_collision.GetPosition();
	auto playerPosition = glm::vec3(collisionPosition.x, 0.f, collisionPosition.y);

	const float velocity = GetCurrentLinearVelocity(dt);
	const float rotationSpeed = GetCurrentRotationSpeed(dt);

	auto direction = GetDirection();
	auto linearVelocity = dt * direction * velocity;
	m_collision.ApplyAcceleration(glm::vec2(linearVelocity.x, linearVelocity.z));

	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();

}

void CLifeObject::ResetWeapon()
{
	m_weapon.SetState(CWeapon::IdState::NotActive);
}

void CLifeObject::Shoot()
{
	auto collisionPosition = m_collision.GetPosition();
	auto entityPosition = glm::vec3(collisionPosition.x, 0.f, collisionPosition.y);

	auto direction = GetDirection();
	m_world->CreateShoot(entityPosition
		, glm::vec3(direction.x, direction.y, direction.z)
		, m_weapon.GetTypeShoot());
}