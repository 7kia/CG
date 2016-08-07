#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	: IUpdatable()
	, CHavePosition()
	, CHaveDirection(PlayerSpace::PLAYER_DIRECTION)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
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
