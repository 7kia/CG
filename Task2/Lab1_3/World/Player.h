#pragma once

#include "../Mixin/Updatable.h"
#include "../Mixin/HaveLinearVelocity.h"
#include "../Mixin/HaveRotationSpeed.h"
#include "../Mixin/HaveDirection.h"

#include "..\Camera\PlayerCamera.h"
#include "..\DispatchEvent.h"
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>

namespace PlayerSpace
{
	const glm::vec3 PLAYER_DIRECTION = { 1.f, 0.f, 0.f };

	const float ROTATION_SPEED_RADIANS = 1.f;
	const float LINEAR_MOVE_SPEED = 5.f;

}

//
// SSkill - content pointer to function and value keys which activate the skill
// 
struct SSkill
{
	SSkill() = default;
	SSkill(std::function<void()> function, const std::vector<SDL_Keysym> & keys);

	std::function<void()>	m_skill = nullptr;
	std::vector<SDL_Keysym>	m_keys;
};

class CPlayer final
	: public IUpdatable
	, public CHavePosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
{
public:
	CPlayer();
	explicit CPlayer(const glm::vec3 & position, const glm::vec3 & direction);
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
public:
	class CController;
	std::unique_ptr<CController> m_pController;// TODO : see need pImpl and unique_ptr

private:
	CPlayerCamera			m_camera;
};