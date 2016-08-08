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

	const float ROTATION_SPEED_RADIANS = 45.f;
	const float LINEAR_MOVE_SPEED = 75.f;

}

//
// SSkill - content pointer to function and value keys which activate the skill
// 

class CPlayer final
	: public IUpdatable
	, public CHavePosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
{
public:
	CPlayer();
	explicit CPlayer(const glm::vec3 & position
					, const glm::vec3 & direction
					, CAbcstartCamera* camera);
//////////////////////////////////////////////////////////////////////
// Methods
public:

	using KeyList = std::vector<SDL_Keycode>;
	struct SSkill
	{
		SSkill() = default;
		SSkill(const std::function<void()> function, const KeyList & keys);
		
		std::function<void()>		m_skill	= nullptr;
		KeyList						m_keys;
	};

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
	void							SetCamera(CAbcstartCamera * camera);
	CAbcstartCamera*				GetCamera();// TODO : see need there const

private:
//////////////////////////////////////////////////////////////////////
// Data
public:
	class CController;
	std::unique_ptr<CController>	m_pController;// TODO : see need pImpl and unique_ptr

private:
	CAbcstartCamera*				m_camera = nullptr;
};

class CPlayer::CController
	: public IInputEventAcceptor
{
public:
	CController(CPlayer * master);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	enum class IdCommands
	{
		TurnToLeft = 0
		, TurnToRight
		, GoToForward
		, GoToBack
		, AmountCommands
	};

	void				OnKeyDown(const SDL_KeyboardEvent &event) override;
	void				OnKeyUp(const SDL_KeyboardEvent &event) override;
private:
	void				SetSkill(IdCommands id, const std::function<void()> function);
	void				SetKeysSkill(IdCommands id, const KeyList & keys);

	IdCommands			FindCommand(const SDL_KeyboardEvent & event);

	void				SetFunctionList();
	void				CheckListCommands() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CPlayer*							m_master;
	std::map<IdCommands, SSkill>		m_listFunctions;
};
