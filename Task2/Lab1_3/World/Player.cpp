#include "stdafx.h"
#include "Player.h"
#include "World.h"

CPlayer::SSkill::SSkill(const std::function<void()> function
						, const KeyList & keys
						, const EventType type)
{
	m_skill = function;
	m_keys = keys;
	m_type = type;
}

CPlayer::CPlayer()
	: IActor()
	, CHave3DPosition()
	, CHaveDirection(PlayerSpace::PLAYER_DIRECTION)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_flashlight(GL_LIGHT1)
	, m_pController(std::make_unique<CController>(this))
	, m_visual(16, 16)
{
	m_collision.SetPVisual(&m_visual);
	SetCameras(PlayerSpace::PLAYER_DIRECTION);
}

CPlayer::CPlayer(const glm::vec3 & position
				, const glm::vec3 & direction
				, const std::string & texturePath
				, CWorld* pWorld)
	: IActor()
	, CHave3DPosition()
	, CHaveDirection()
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_flashlight(GL_LIGHT1)
	, m_visual(16, 16)
	, m_pController(std::make_unique<CController>(this))
{
	SetTexture(texturePath);
	SetCameras(PlayerSpace::PLAYER_DIRECTION);
	CreatePlayer(position, direction, pWorld);
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
	m_collision.ResetVelocity();
	auto collisionPosition = m_collision.GetPosition();
	auto playerPosition = glm::vec3(collisionPosition.x, 0.f, collisionPosition.y);
	GetCamera()->SetPosition(playerPosition);

	const float velocity = GetCurrentLinearVelocity(deltaTime);
	const float rotationSpeed = GetCurrentRotationSpeed(deltaTime);
	GetCamera()->Update(deltaTime
						, velocity
						, rotationSpeed);

	auto direction = GetCamera()->GetCurrentDirection();
	auto linearVelocity = deltaTime * direction * velocity;
	m_collision.ApplyAcceleration(glm::vec2(linearVelocity.x, linearVelocity.z));


	playerPosition.y = PlayerSpace::HEIGHT_VISUAL_PART;
	if (m_idCamera == IdCameras::Player)
	{
		m_visual.SetTransform(glm::translate(glm::mat4(), playerPosition));
		m_collision.Advance(deltaTime);
		m_flashlight.SetPosition(GetCamera()->GetPosition());
	}

	//m_flashlight.SetDirection(direction);
	ResetCurrentLinearVelocity();
	ResetCurrentRotationSpeed();
}

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

	m_texture->DoWhileBinded([&] {
		m_visual.Draw();
	});
}

void CPlayer::SetCamera(CPlayer::IdCameras id)
{
	m_idCamera = id;
}

CAbstractRotatableCamera* CPlayer::GetCamera()
{
	return m_cameras[unsigned(m_idCamera)].get();// TODO : see word it
}

void CPlayer::SetCameras(const glm::vec3 & direction)
{
	m_cameras[unsigned(IdCameras::Player)] = std::make_unique<CPlayerCamera>();
	m_cameras[unsigned(IdCameras::Player)]->SetDirection(direction);

	m_cameras[unsigned(IdCameras::World)] = std::make_unique<CWorldCamera>(0.f, 15.5f);

	SetCamera(IdCameras::Player);
}


void CPlayer::SetCollison(CWorld* pWorld)
{
	m_collision.SetRadius(1.f);
	m_collision.SetReferenceSystemOrigin(glm::vec2());

	auto position = GetCamera()->GetPosition();
	m_collision.SetPosition(position.x, position.y);
	m_collision.SetVelocity(glm::vec2());


	//m_visual.SetType(m_pWorld->GetWallType(0));
	m_visual.SetTransform(glm::translate(glm::mat4(), position));

	m_collision.AddToWorld(pWorld->GetWorld());
}

void CPlayer::CreatePlayer(const glm::vec3 & position
	, const glm::vec3 & direction
	, CWorld* pWorld)
{
	m_collision.SetPVisual(&m_visual);

	SetCameras(direction);

	GetCamera()->SetPosition(position);
	SetCollison(pWorld);

	m_flashlight.SetPosition(position);
	m_flashlight.SetDiffuse(PlayerSpace::WHITE_RGBA);
	m_flashlight.SetAmbient(0.1f * PlayerSpace::WHITE_RGBA);
	m_flashlight.SetSpecular(PlayerSpace::WHITE_RGBA);
}
