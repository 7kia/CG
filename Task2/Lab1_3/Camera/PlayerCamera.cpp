#include "stdafx.h"
#include "PlayerCamera.h"



CPlayerCamera::CPlayerCamera(const glm::vec3 & position, const glm::vec3 & direction)
	: CAbcstartCamera()
	, CHavePosition(position)
	, CHaveDirection(PlayerCameraSpace::PLAYER_DIRECTION)
{
}

void CPlayerCamera::Update(float deltaSec)
{
	m_rotationRadians += deltaSec * PlayerCameraSpace::GetRotationSpeedRadians(m_keysPressed);
	auto direction = GetDirection();
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians);

	glm::vec3 direction3D = glm::vec3(direction.x, direction.y, direction.z);


	Move(direction3D * (deltaSec * PlayerCameraSpace::GetLinearMoveSpeed(m_keysPressed)) );
}

glm::mat4 CPlayerCamera::GetViewTransform() const
{
	auto direction = GetDirection();
	// ����������� ������ (�������� � ��������� �����),
	// ����� ������������ ������ ��� Z.
	// ��. http://glm.g-truc.net/0.9.3/api/a00199.html
	direction = glm::rotateY(glm::normalize(direction), m_rotationRadians);

	const glm::vec3 eye = GetPosition();
	const glm::vec3 center = eye + glm::vec3(direction.x, direction.y, direction.z);//direction
	const glm::vec3 up = { 0, 1, 0 };

	// ������� �������������-���� ����������� �������� glm::lookAt.
	// ��� ��� �������, ����������� ���, ��� ����� ������ �������
	// � ������� eye �� ����� center, � ����������� "�����" ������ ����� up.
	return glm::lookAt(eye, center, up);
}
