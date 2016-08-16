#include "stdafx.h"
#include "Player.h"


CPlayer::SSkill::SSkill(const std::function<void()> function, const KeyList & keys)
{
	m_skill = function;
	m_keys = keys;
}

CPlayer::CPlayer()
	: IActor()
	, CHave3DPosition()
	, CHaveDirection(PlayerSpace::PLAYER_DIRECTION)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_flashlight(GL_LIGHT1)
	, m_pController(std::make_unique<CController>(this))
{
	m_collision.SetPVisual(&m_visual);
	SetCameras();
}

CPlayer::CPlayer(const glm::vec3 & position
				, const glm::vec3 & direction
				, CWorld* pWorld)
	: IActor()
	, CHave3DPosition()
	, CHaveDirection()
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_flashlight(GL_LIGHT1)
	, m_pController(std::make_unique<CController>(this))
{
	SetCameras();
	CreatePlayer(position, direction, pWorld);
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
	m_collision.ReserVelocity();
	auto collisionPosition = m_collision.GetPosition();
	GetCamera()->SetPosition(glm::vec3(collisionPosition.x, 0.f, collisionPosition.y));

	GetCamera()->Update(deltaTime
				, GetCurrentLinearVelocity()
				, GetCurrentRotationSpeed());
	//SetPosition(GetCamera()->GetPosition());// TODO : might need rewrite, the string crutch

	auto linearVelocity = deltaTime * GetCamera()->GetCurrentDirection() * GetCurrentLinearVelocity();
	m_collision.ApplyAcceleration(glm::vec2(linearVelocity.x, linearVelocity.z));
	//m_collision.ApplyAcceleration(glm::vec2(deltaTime, deltaTime));

	m_collision.Advance(deltaTime);

	m_flashlight.SetPosition(GetPosition());
	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();
}

void CPlayer::Draw() const
{
	//m_flashlight.Setup();// TODO : fix light
	m_visual.Draw();
}

void CPlayer::SetCamera(CPlayer::IdCameras id)
{
	m_idCamera = id;
}

CAbstractRotatableCamera* CPlayer::GetCamera()
{
	return m_cameras[unsigned(m_idCamera)].get();// TODO : see word it
}

void CPlayer::SetCameras()
{
	m_cameras[unsigned(IdCameras::Player)] = std::make_unique<CPlayerCamera>();
	m_cameras[unsigned(IdCameras::World)] = std::make_unique<CWorldCamera>(0.f, 2.5f);

	SetCamera(IdCameras::Player);
}
