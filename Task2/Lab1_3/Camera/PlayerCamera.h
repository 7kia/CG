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


}


// TODO : rename
class CPlayerCamera final
	: public CAbcstartCamera
	, public CHavePosition
	, public CHaveDirection
	, private boost::noncopyable
{
public:
	CPlayerCamera() = default;
	explicit CPlayerCamera(const glm::vec3 & position, const glm::vec3 & direction);
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//--------------------------------------------
	// IUpdatable
	void		Update(float deltaSec
						, float moveSpeed
						, float rotationSpeed);
	//--------------------------------------------
	// IInputEventAcceptor
	glm::mat4	GetViewTransform() const override final;
	//--------------------------------------------

//////////////////////////////////////////////////////////////////////
// Data
private:
	float		m_rotationRadians = 0;
};
