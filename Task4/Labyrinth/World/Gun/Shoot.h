#pragma once

#include "../Actor.h"
#include "Mixin/HaveLinearVelocity.h"
#include "Mixin/HaveRotationSpeed.h"
#include "Mixin/HaveDirection.h"
#include "Mixin/Drawable.h"
#include "Mixin/Material/HaveTexture.h"
#include "2DShape/2DCircleCollision.h"
#include "3DShape\3DSphere.h"
#include "Lights.h"
#include "Camera\Cameras.h"
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <array>

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
	, public CHaveTexture
{
public:
	CShoot();
	explicit CShoot(const glm::vec3 & position
		, const glm::vec3 & direction
		, const std::string & texturePath// TODO : create types
		, CWorld* pWorld);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	
	//--------------------------------------------
	// IActor
	void							Update(float deltaTime) override final;
	void							Draw() const override final;
	//--------------------------------------------
private:

	void							SetCollison(CWorld* pWorld);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	C2DCircleCollision				m_collision;
	CIdentity3DSphere				m_visual;
};