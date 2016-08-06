#pragma once

#include "Camera.h"
#include "../Mixin/HavePosition.h"
#include "../Mixin/HaveDirection.h"

namespace PlayerCameraSpace
{
	const glm::vec3 PLAYER_DIRECTION = { 1.f, 0.f, 0.f };

	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 5.f;
	const float MIN_DISTANCE = 1.5f;
	const float MAX_DISTANCE = 30.f;

	static float GetRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
		{
			return ROTATION_SPEED_RADIANS;
		}
		return 0;
	}

	static float GetLinearMoveSpeed(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
		{
			return LINEAR_MOVE_SPEED;
		}
		if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
		{
			return -LINEAR_MOVE_SPEED;
		}
		return 0;
	}
}


// TODO : rename
class CPlayerCamera
	: public CAbcstartCamera
	, public CHavePosition
	, public CHaveDirection
	, private boost::noncopyable
{
public:
	explicit CPlayerCamera(const glm::vec3 & position, const glm::vec3 & direction);
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//--------------------------------------------
	// IUpdatable
	void		Update(float deltaSec) override;
	//--------------------------------------------
	// IInputEventAcceptor
	glm::mat4	GetViewTransform() const override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Data
private:
	float		m_rotationRadians = 0;
};
