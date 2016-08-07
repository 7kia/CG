#include "stdafx.h"
#include "Player.h"


CPlayer::SSkill::SSkill(const std::function<void()> function, const KeyList & keys)
{
	m_skill = function;
	m_keys = keys;
}

CPlayer::CPlayer()
	: IUpdatable()
	, CHavePosition()
	, CHaveDirection(PlayerSpace::PLAYER_DIRECTION)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_pController(std::make_unique<CController>(this))
{
}

CPlayer::CPlayer(const glm::vec3 & position, const glm::vec3 & direction)
	: IUpdatable()
	, CHavePosition(position)
	, CHaveDirection(direction)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_pController(std::make_unique<CController>(this))
	, m_camera(position, direction)
{
}

void CPlayer::TurnLeft()
{
	SetCurrentRotationSpeed(GetRotationSpeed());
}

void CPlayer::TurnRight()
{
	SetCurrentRotationSpeed(-GetRotationSpeed());
}

void CPlayer::GoForward()
{
	SetCurrentLinearVelocity(GetLinearVelocity());
}

void CPlayer::GoBack()
{
	SetCurrentLinearVelocity(-GetLinearVelocity());
}

void CPlayer::Update(float deltaTime)
{
	m_camera.Update(deltaTime
		, GetCurrentLinearVelocity()
		, GetCurrentRotationSpeed());
	SetPosition(m_camera.GetPosition());// TODO : might need rewrite, the string crutch

	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();
}

CAbcstartCamera * CPlayer::GetPlayerCamera()
{
	return &m_camera;
}
