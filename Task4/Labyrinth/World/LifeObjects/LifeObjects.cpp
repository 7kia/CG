#include "LifeObjects.h"

using namespace cocos2d;

CLifeObject::CLifeObject()
	: IActor()
	, CHave3DPosition()
	, CHaveDirection()
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_visual(16, 16)
{
}

CLifeObject(const glm::vec3 & position
		, const glm::vec3 & direction
		, const std::string & texturePath
		, CWorld* pWorld)
	: IActor()
	, CHave3DPosition()
	, CHaveDirection()
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_visual(16, 16)
{

}

CLifeObject::~CLifeObject()
{
}



void CLifeObject::SetType(TypeLifeObject & setType)
{
	m_type.reset(&setType);

	setTexture(m_type->GetTexture());
	setTextureRect(m_type->GetTextureRectangle());

	CreateCollision();

	SetVelocity(m_type->GetVelocity());

	m_health.SetValue(m_type->GetHealth());

	m_weapon.SetType(m_type->GetTypeWeapon());

}

void CLifeObject::SetCollison(CWorld* pWorld)
{
	m_collision.SetRadius(1.f);
	m_collision.SetReferenceSystemOrigin(glm::vec2());

	auto position = GetCamera()->GetPosition();
	m_collision.SetPosition(position.x, position.y);
	m_collision.SetVelocity(glm::vec2());

	m_visual.SetTransform(glm::translate(glm::mat4(), position));

	m_collision.AddToWorld(pWorld->GetWorld());
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

void CLifeObject::SetWeapon(const CTypeWeapon & typeWeapon)
{
	m_weapon.SetType(typeWeapon);
}
