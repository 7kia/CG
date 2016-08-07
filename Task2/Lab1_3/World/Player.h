#pragma once

#include "../Mixin/Updatable.h"
#include "../Mixin/HaveLinearVelocity.h"
#include "../Mixin/HaveRotationSpeed.h"
#include "../Mixin/HaveDirection.h"

#include "..\Camera\PlayerCamera.h"

namespace PlayerSpace
{
	const glm::vec3 PLAYER_DIRECTION = { 1.f, 0.f, 0.f };

	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 5.f;

}

class CPlayer final
	: public IUpdatable
	, public CHavePosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
{
public:
	CPlayer();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// TODO : see might the enums need transfer to heirs
	enum class TurnTo
	{
		Left = 0
		, Right
	};
	// TODO : transfer four low methods to skill-function
	void TurnLeft();
	void TurnRight();

	enum class GoTo
	{
		Forward = 0
		, Back
	};

	void GoForward();
	void GoBack();
	//--------------------------------------------
	// IUpdatable
	void Update(float deltaTime) override final;
	//--------------------------------------------
private:

//////////////////////////////////////////////////////////////////////
// Data
private:
	CPlayerCamera	m_camera;
};