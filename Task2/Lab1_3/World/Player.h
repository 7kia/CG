#pragma once

#include "../Mixin/Updatable.h"
#include "../Mixin/HaveLinearVelocity.h"
#include "../Mixin/HaveRotationSpeed.h"
#include "../Mixin/HaveDirection.h"
#include "../Mixin/Drawable.h"

#include "../Lights.h"
#include "..\Camera\Cameras.h"
#include "..\DispatchEvent.h"
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <array>

namespace PlayerSpace
{
	const glm::vec3 PLAYER_DIRECTION = { 1.f, 0.f, 0.f };

	const float ROTATION_SPEED_RADIANS = 5.f;
	const float LINEAR_MOVE_SPEED = 25.f;


		const glm::vec4 BLACK = { 0, 0, 0, 1 };
		const float MATERIAL_SHININESS = 30.f;
		const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
		const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
		const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
		const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };
		const float CAMERA_INITIAL_ROTATION = 0;
		const float CAMERA_INITIAL_DISTANCE = 5.f;


}

//
// SSkill - content pointer to function and value keys which activate the skill
// 

class CPlayer final
	: public IUpdatable
	, public IDrawable
	, public CHavePosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
{
public:
	CPlayer();
	explicit CPlayer(const glm::vec3 & position
					, const glm::vec3 & direction);
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
	enum class IdCameras
	{
		Player = 0
		, World
	};

	// TODO : transfer four low methods to skill-function
	void TurnLeft();
	void TurnRight();

	void GoForward();
	void GoBack();

	void ChangePlayerCamera();
	void ChangeWorldCamera();

	//--------------------------------------------
	// IUpdatable
	void Update(float deltaTime) override final;
	//--------------------------------------------
	// IDrawable
	void Draw() const override final;
	//--------------------------------------------
	void							SetCamera(CPlayer::IdCameras id);
	CAbcstartCamera*				GetCamera();// TODO : see need there const

private:
	void							SetCamera();
//////////////////////////////////////////////////////////////////////
// Data
public:
	class CController;
	std::unique_ptr<CController>	m_pController;// TODO : see need pImpl and unique_ptr

private:
	IdCameras						m_idCamera = IdCameras::Player;
	// TODO : see might can rewrite better
	std::array<std::unique_ptr<CAbcstartCamera>, 2>	m_cameras;

	CPositionLightSource			m_flashlight;
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
		, ChangePlayerCamera
		, ChangeWorldCamera
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
