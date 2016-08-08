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
	auto direction4d = GetDirection();
	glm::vec3 direction = { direction4d.x, direction4d.y, direction4d.z };
	// ����������� ������ (�������� � ��������� �����),
	// ����� ������������ ������ ��� Z.
	// ��. http://glm.g-truc.net/0.9.3/api/a00199.html
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians);

	const glm::vec3 eye = direction * m_distance;// TODO : must position = eye

	const glm::vec3 center = { 0, 0, 0 };//direction
	const glm::vec3 up = { 0, 1, 0 };

	// ������� �������������-���� ����������� �������� glm::lookAt.
	// ��� ��� �������, ����������� ���, ��� ����� ������ �������
	// � ������� eye �� ����� center, � ����������� "�����" ������ ����� up.
	return glm::lookAt(eye, center, up);
}

