#pragma once

#include "Camera.h"

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
	: public CAbstractRotatableCamera
	, private boost::noncopyable
{
public:
	CPlayerCamera() = default;
	explicit CPlayerCamera(const glm::vec3 & position, const glm::vec3 & direction);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		Update(float deltaSec
						, float moveSpeed
						, float rotationSpeed) override;

	glm::mat4	GetViewTransform() const override final;
//////////////////////////////////////////////////////////////////////
// Data
private:
};
