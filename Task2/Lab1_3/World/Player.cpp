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
	SetCamera();
}

CPlayer::CPlayer(const glm::vec3 & position
				, const glm::vec3 & direction)
	: IUpdatable()
	, CHavePosition(position)
	, CHaveDirection(direction)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_pController(std::make_unique<CController>(this))
{
	SetCamera();

	GetCamera()->SetPosition(position);
	GetCamera()->SetDirection(direction);
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

void CPlayer::ChangePlayerCamera()
{
	m_idCamera = IdCameras::Player;
}

void CPlayer::ChangeWorldCamera()
{
	m_idCamera = IdCameras::World;
}

/*
void CPlayer::ChangeCamera()
{
	if (m_idCamera == IdCameras::Player)
	{
		m_idCamera = IdCameras::World;
	}
	else
	{
		m_idCamera = IdCameras::Player;
	}
}
*/


void CPlayer::Update(float deltaTime)
{
	GetCamera()->Update(deltaTime
					, GetCurrentLinearVelocity()
					, GetCurrentRotationSpeed());
	SetPosition(GetCamera()->GetPosition());// TODO : might need rewrite, the string crutch

	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();
}

void CPlayer::SetCamera(CPlayer::IdCameras id)
{
	m_idCamera = id;
}

CAbcstartCamera * CPlayer::GetCamera()
{
	return m_cameras[unsigned(m_idCamera)].get();
}

void CPlayer::SetCamera()
{
	m_cameras[unsigned(IdCameras::Player)] = std::make_unique<CPlayerCamera>();
	m_cameras[unsigned(IdCameras::World)] = std::make_unique<CWorldCamera>(0.f, 2.5f);

	SetCamera(IdCameras::Player);
}
