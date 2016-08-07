#include "stdafx.h"
#include "Player.h"


SSkill::SSkill(std::function<void()> function, const std::vector<SDL_Keysym> & keys)
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
}

CPlayer::CPlayer(const glm::vec3 & position, const glm::vec3 & direction)
	: IUpdatable()
	, CHavePosition(position)
	, CHaveDirection(direction)
	, CHaveLinearVelocity(PlayerSpace::LINEAR_MOVE_SPEED)
	, CHaveRotationSpeed(PlayerSpace::ROTATION_SPEED_RADIANS)
	, m_pController(std::make_unique<CController>(this))
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
	void				SetKeysSkill(IdCommands id, const std::vector<SDL_Keysym> & keys);


	void				SetFunctionList();
	void				CheckListCommands() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	CPlayer*							m_master;
	std::map<IdCommands, SSkill>		m_listFunctions;
};

CPlayer::CController::CController(CPlayer * master)
	: IInputEventAcceptor()
	, m_master(master)
{
	for (short id = 0; id < short(IdCommands::AmountCommands); ++id)
	{
		m_listFunctions.insert({ IdCommands(id), SSkill() });
	}

	SetFunctionList();
	CheckListCommands();
}

void CPlayer::CController::OnKeyDown(const SDL_KeyboardEvent & event)
{
	if (std::find(m_listFunctions.begin(), m_listFunctions.end(), event.keysym) != m_listFunctions.end())
	{
		m_listFunctions[event.keysym];
	}
}

void CPlayer::CController::SetSkill(IdCommands id, const std::function<void()> function)
{
	m_listFunctions[id].m_skill = function;
}

void CPlayer::CController::SetKeysSkill(IdCommands id, const std::vector<SDL_Keysym>& keys)
{
	m_listFunctions[id].m_keys = keys;

}

void CPlayer::CController::SetFunctionList()
{
	SetSkill(IdCommands::GoToForward, m_master->GoForward);


	m_listFunctions[IdCommands::GoToForward] = SSkill(, { SDLK_UP, SDLK_UP } );
	m_listFunctions[IdCommands::GoToBack] = m_master->GoBack;
	m_listFunctions[IdCommands::TurnToLeft] = m_master->TurnLeft;
	m_listFunctions[IdCommands::TurnToRight] = m_master->TurnRight;

	m_listFunctions[IdCommands::GoToForward] = m_master->GoForward;
	m_listFunctions[IdCommands::GoToBack] = m_master->GoBack;
	m_listFunctions[IdCommands::TurnToLeft] = m_master->TurnLeft;
	m_listFunctions[IdCommands::TurnToRight] = m_master->TurnRight;

}

void CPlayer::CController::CheckListCommands() const
{
	for (const auto & element : m_listFunctions)
	{
		if (element.second.skill == nullptr)
		{
			throw std::runtime_error("No function with id " + std::to_string(short(element.first)));
		}
	}
};
