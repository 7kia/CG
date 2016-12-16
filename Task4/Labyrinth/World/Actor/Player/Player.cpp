#include "stdafx.h"
#include "Player.h"
#include "World\World.h"


CPlayerController::SSkill::SSkill(const std::function<void()> function
						, const KeyList & keys
						, const EventType type)
{
	m_skill = function;
	m_keys = keys;
	m_type = type;
}

CPlayer::CPlayer()
	: CLifeObject()
	, m_flashlight(GL_LIGHT1)
	, m_pController(this)
{
	SetCameras(PlayerSpace::PLAYER_DIRECTION);
}

CPlayer::CPlayer(CLifeObjectType & type
				, CWorld* pWorld
				, const glm::vec3 & position
				, const glm::vec3 & direction)
	: CLifeObject(type, pWorld, position, direction)
	, m_flashlight(GL_LIGHT1)
	, m_pController(this)
{
	SetCameras(direction);

	GetCamera()->SetPosition(position);

	m_flashlight.SetPosition(position);
	m_flashlight.SetDiffuse(PlayerSpace::WHITE_RGBA);
	m_flashlight.SetAmbient(0.1f * PlayerSpace::WHITE_RGBA);
	m_flashlight.SetSpecular(PlayerSpace::WHITE_RGBA);
}

void CPlayer::TurnLeft()
{
	m_directionRotation = DirectionRotation::Left;
}

void CPlayer::TurnRight()
{
	m_directionRotation = DirectionRotation::Right;
}

void CPlayer::ResetDirectionRotation()
{
	m_directionRotation = DirectionRotation::None;
}

void CPlayer::GoForward()
{
	m_directionWalk = DirectionWalk::Forward;
}

void CPlayer::GoBack()
{
	m_directionWalk = DirectionWalk::Back;
}

void CPlayer::ResetDirectionWalk()
{
	m_directionWalk = DirectionWalk::None;
}

void CPlayer::ChangePlayerCamera()
{
	m_idCamera = IdCameras::Player;
}

void CPlayer::ChangeWorldCamera()
{
	m_idCamera = IdCameras::World;
}

void CPlayer::SwitchFlashLight()
{
	m_isFlashLightOn = !m_isFlashLightOn;
}

void CPlayer::SwitchPlayState()
{
	m_world->SwitchPlayState();
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

void CPlayer::Draw() const
{
	if (m_isFlashLightOn)
	{
		m_flashlight.Setup();// TODO : fix light
	}
	else
	{
		m_flashlight.Disable();
	}
	//m_flashlight.Draw();

	CLifeObject::Draw();
}

void CPlayer::UpdatePosition(float dt)
{

	m_collision.ResetVelocity();
	auto collisionPosition = m_collision.GetPosition();
	auto playerPosition = glm::vec3(collisionPosition.x, 0.f, collisionPosition.y);
	GetCamera()->SetPosition(playerPosition);

	const float velocity = GetCurrentLinearVelocity(dt);
	const float rotationSpeed = GetCurrentRotationSpeed(dt);
	GetCamera()->Update(dt
		, velocity
		, rotationSpeed);

	auto direction = GetCamera()->GetCurrentDirection();

	SetDirection(direction);
	SetPosition(playerPosition);

	auto linearVelocity = dt * direction * velocity;
	m_collision.ApplyAcceleration(glm::vec2(linearVelocity.x, linearVelocity.z));


	if (m_idCamera == IdCameras::Player)
	{
		m_visual.SetTransform(glm::translate(glm::mat4(), playerPosition));
		m_collision.Advance(dt);

		playerPosition += direction * 2.f;
		//playerPosition.y = PlayerSpace::HEIGHT_FLASHLIGHT;
		m_flashlight.SetPosition(playerPosition);
	}

	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();
}

void CPlayer::SetCamera(CPlayer::IdCameras id)
{
	m_idCamera = id;
}

CAbstractRotatableCamera* CPlayer::GetCamera()
{
	return m_cameras[size_t(m_idCamera)].get();// TODO : see word it
}

void CPlayer::SetCameras(const glm::vec3 & direction)
{
	m_cameras[size_t(IdCameras::Player)] = std::make_unique<CPlayerCamera>();
	m_cameras[size_t(IdCameras::Player)]->SetDirection(direction);

	m_cameras[size_t(IdCameras::World)] = std::make_unique<CWorldCamera>(0.f, 15.5f);

	SetCamera(IdCameras::Player);
}
