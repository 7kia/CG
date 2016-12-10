#include "stdafx.h"
#include "WorldCamera.h"

namespace WorldCameraSpace
{
	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 15.f;
	const float MIN_DISTANCE = 1.5f;
	const float MAX_DISTANCE = 30.f;
}

CWorldCamera::CWorldCamera(float rotationRadians, float distance)
	: CAbstractRotatableCamera(rotationRadians)
	, m_distance(distance)
{
	SetDirection({ 0.f, 0.5f, 1.f });
}

void CWorldCamera::Update(float deltaSec
						, float moveSpeed
						, float rotationSpeed)
{
	m_rotationRadians += deltaSec * rotationSpeed;
	m_distance -= deltaSec * moveSpeed;
	m_distance = glm::clamp(m_distance, WorldCameraSpace::MIN_DISTANCE, WorldCameraSpace::MAX_DISTANCE);
}

glm::mat4 CWorldCamera::GetViewTransform() const
{
	const glm::vec3 eye = GetCurrentDirection() * m_distance;

	const glm::vec3 center = { 0, 0, 0 };
	const glm::vec3 up = { 0, 1, 0 };

	// Матрица моделирования-вида вычисляется функцией glm::lookAt.
	// Она даёт матрицу, действующую так, как будто камера смотрит
	// с позиции eye на точку center, а направление "вверх" камеры равно up.
	return glm::lookAt(eye, center, up);
}

