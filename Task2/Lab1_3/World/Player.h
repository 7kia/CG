#pragma once

#include "Actor.h"
#include "../Mixin/HaveLinearVelocity.h"
#include "../Mixin/HaveRotationSpeed.h"
#include "../Mixin/HaveDirection.h"
#include "../Mixin/Drawable.h"
#include "../Mixin/Material/HaveTexture.h"
#include "../2DShape/2DCircleCollision.h"
#include "3DShape\3DSphere.h"
#include "..\Lights.h"
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
	const float LINEAR_MOVE_SPEED = 150.f;
	const float HEIGHT_FLASHLIGHT = 1.5f;

	const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
}

class CWorld;

class CPlayer final
	: public IActor
	, public CHave3DPosition
	, public CHaveDirection
	, public CHaveLinearVelocity
	, public CHaveRotationSpeed
	, public CHaveTexture
{
public:
	CPlayer();
	explicit CPlayer(const glm::vec3 & position
					, const glm::vec3 & direction
					, const std::string & texturePath
					, CWorld* pWorld);
//////////////////////////////////////////////////////////////////////
// Methods
public:

	//
	// SSkill - content pointer to function and value keys which activate the skill
	// 
	using KeyList = std::vector<SDL_Keycode>;
	using EventType = Uint32;
	struct SSkill
	{
		SSkill() = default;
		SSkill(const std::function<void()> function
				, const KeyList & keys
				, const EventType type);
		
		std::function<void()>		m_skill	= nullptr;
		KeyList						m_keys;
		EventType					m_type;
	};
	enum class IdCameras
	{
		Player = 0
		, World
	};
	//--------------------------------------------
	// IActor
	void							Update(float deltaTime) override final;
	void							Draw() const override final;
	//--------------------------------------------

	void							CreatePlayer(const glm::vec3 & position
												, const glm::vec3 & direction
												, CWorld* pWorld
												, const std::string & pathTexture);
	CAbstractRotatableCamera*		GetCamera();// TODO : see need there cons

private:
	////////////////////////////////////////////////////////////
	// Commands
	void							TurnLeft();
	void							TurnRight();
	void							ResetDirectionRotation();

	void							GoForward();
	void							GoBack();
	void							ResetDirectionWalk();

	void							ChangePlayerCamera();
	void							ChangeWorldCamera();

	void							SwitchFlashLight();
	////////////////////////////////////////////////////////////


	void							SetCamera(CPlayer::IdCameras id);

	void							SetCameras(const glm::vec3 & direction);
	void							SetCollison(CWorld* pWorld);
//////////////////////////////////////////////////////////////////////
// Data
public:
	class CController;
	std::unique_ptr<CController>	m_pController;
private:
	IdCameras						m_idCamera = IdCameras::Player;
	// TODO : see might can rewrite better
	std::array<std::unique_ptr<CAbstractRotatableCamera>, 2>	m_cameras;

	CPositionLightSource			m_flashlight;
	bool							m_isFlashLightOn = true;

	C2DCircleCollision				m_collision;
	CIdentity3DSphere				m_visual;
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
		, ResetDirectionRotation
		, GoToForward
		, GoToBack
		, ResetDirectionWalk
		, ChangePlayerCamera
		, ChangeWorldCamera
		, SwitchFlashLight
		, AmountCommands
	};

	void				OnKeyDown(const SDL_KeyboardEvent &event) override;
	void				OnKeyUp(const SDL_KeyboardEvent &event) override;
private:
	void				SetSkill(IdCommands id, const std::function<void()> function);
	void				SetKeysSkill(IdCommands id
									, const CPlayer::KeyList & keys
									, const CPlayer::EventType type);

	IdCommands			FindCommand(const SDL_KeyboardEvent & event, const EventType type);

	void				SetFunctionList();
	void				CheckListCommands() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	CPlayer*							m_master = nullptr;// TODO : see might need do it smart pointer
	std::map<IdCommands, SSkill>		m_listFunctions;
};
