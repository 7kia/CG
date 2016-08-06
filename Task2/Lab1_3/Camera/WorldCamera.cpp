#include "stdafx.h"
#include "WorldCamera.h"

namespace WorldCameraSpace
{
	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 15.f;
	const float MIN_DISTANCE = 1.5f;
	const float MAX_DISTANCE = 30.f;

	float GetRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_RIGHT) || keysPressed.count(SDLK_d))
		{
			return ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_LEFT) || keysPressed.count(SDLK_a))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		return 0;
	}

	float GetLinearMoveSpeed(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_UP) || keysPressed.count(SDLK_w))
		{
			return -LINEAR_MOVE_SPEED;
		}
		if (keysPressed.count(SDLK_DOWN) || keysPressed.count(SDLK_s))
		{
			return +LINEAR_MOVE_SPEED;
		}
		return 0;
	}
}

CWorldCamera::CWorldCamera(float rotationRadians, float distance)
	: m_rotationRadians(rotationRadians)
	, m_distance(distance)
{
}

void CWorldCamera::Update(float deltaSec)
{
	m_rotationRadians += deltaSec * WorldCameraSpace::GetRotationSpeedRadians(m_keysPressed);
	m_distance += deltaSec * WorldCameraSpace::GetLinearMoveSpeed(m_keysPressed);
	m_distance = glm::clamp(m_distance, WorldCameraSpace::MIN_DISTANCE, WorldCameraSpace::MAX_DISTANCE);
}

glm::mat4 CWorldCamera::GetViewTransform() const
{
	glm::vec3 direction = { 0.f, 0.5f, 1.f };
	// Нормализуем вектор (приводим к единичной длине),
	// затем поворачиваем вокруг оси Z.
	// см. http://glm.g-truc.net/0.9.3/api/a00199.html
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians);

	const glm::vec3 eye = direction * m_distance;
	const glm::vec3 center = { 0, 0, 0 };//direction
	const glm::vec3 up = { 0, 1, 0 };

	// Матрица моделирования-вида вычисляется функцией glm::lookAt.
	// Она даёт матрицу, действующую так, как будто камера смотрит
	// с позиции eye на точку center, а направление "вверх" камеры равно up.
	return glm::lookAt(eye, center, up);
}

