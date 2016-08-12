#include "stdafx.h"
#include "Camera.h"

CAbcstartCamera::CAbcstartCamera()
	: CHave3DPosition()
	, CHaveDirection()

{
}

CAbstractRotatableCamera::CAbstractRotatableCamera(float rotationRadians)
	: CAbcstartCamera()
	, m_rotationRadians(rotationRadians)
{
}

float CAbstractRotatableCamera::GetRotationRadians() const
{
	return m_rotationRadians;
}

glm::vec3 CAbstractRotatableCamera::GetCurrentDirection() const
{
	auto direction = GetDirection();
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians);

	return glm::vec3(direction.x, direction.y, direction.z);
}
