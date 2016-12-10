#pragma once

#include "Mixin/HaveLinearVelocity.h"
#include "Mixin/HaveDirection.h"
#include "Mixin/Have3DPosition.h"

#include "../Actor.h"

#include "2DShape/2DCircleCollision.h"
#include "3DShape/3DSphere.h"

#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <array>

#include "ShootView.h"

namespace ShootSpace
{
	const glm::vec3 PLAYER_DIRECTION = { 1.f, 0.f, 0.f };

	const float ROTATION_SPEED_RADIANS = 5.f;
	const float LINEAR_MOVE_SPEED = 150.f;
	const float HEIGHT_FLASHLIGHT = 1.5f;

	const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
}

class CWorld;

class CShoot final
	: public IActor
	, public CHave3DPosition
	, public CHaveDirection
	, public CHaveLinearVelocity
{
public:
	CShoot();
	CShoot(const glm::vec3 & position
				, const glm::vec3 & direction
				, const CShootType * type
				, CWorld* pWorld);

	//CShoot &CShoot::operator=(const CShoot & value);
//////////////////////////////////////////////////////////////////////
// Methods
public:

	
	//--------------------------------------------
	// IActor
	void							Update(float deltaTime) override final;
	void							Draw() const override final;
	//--------------------------------------------
	void							SetType(const CShootType* type);
	const CShootType*				GetType() const;

private:

	void							SetCollison(CWorld* pWorld);
//////////////////////////////////////////////////////////////////////
// Data
private:
	C2DCircleCollision				m_collision;
	CShootView						m_visual;
};

using PShoot = std::shared_ptr<CShoot>;