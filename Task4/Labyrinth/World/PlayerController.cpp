#include "stdafx.h"
#include "Player.h"

CPlayerController::CPlayerController(CPlayer * master)
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

void CPlayerController::OnKeyDown(const SDL_KeyboardEvent & event)
{
	
	IdCommands id = FindCommand(event, SDL_KEYDOWN);
	if (id != IdCommands::AmountCommands)
	{
		m_listFunctions[id].m_skill();
	}
}

void CPlayerController::OnKeyUp(const SDL_KeyboardEvent & event)
{
	IdCommands id = FindCommand(event, SDL_KEYUP);
	if (id != IdCommands::AmountCommands)
	{
		m_listFunctions[id].m_skill();
	}
}

void CPlayerController::SetSkill(IdCommands id, const std::function<void()> function)
{
	m_listFunctions[id].m_skill = function;
}

void CPlayerController::SetKeysSkill(IdCommands id
										, const KeyList & keys
										, const EventType type)
{
	m_listFunctions[id].m_keys = keys;
	m_listFunctions[id].m_type = type;
}

CPlayerController::IdCommands CPlayerController::FindCommand(const SDL_KeyboardEvent & event, const EventType type)
{
	for (const auto & element : m_listFunctions)
	{
		const auto & elementType = element.second.m_type;
		if (elementType == type)
		{
			const auto & keys = element.second.m_keys;
			if (std::find(keys.begin(), keys.end(), event.keysym.sym) != keys.end())
			{
				return element.first;
			}
		}	
	}

	return IdCommands::AmountCommands;
}

void CPlayerController::SetFunctionList()
{
	SetSkill(IdCommands::GoToForward, [&]() { m_master->GoForward(); });
	SetKeysSkill(IdCommands::GoToForward, { SDLK_UP, SDLK_w }, SDL_KEYDOWN);

	SetSkill(IdCommands::GoToBack, [&]() { m_master->GoBack(); });
	SetKeysSkill(IdCommands::GoToBack, {SDLK_DOWN, SDLK_s }, SDL_KEYDOWN);

	SetSkill(IdCommands::ResetDirectionWalk, [&]() { m_master->ResetDirectionWalk(); });
	SetKeysSkill(IdCommands::ResetDirectionWalk, { SDLK_UP, SDLK_w, SDLK_DOWN, SDLK_s }, SDL_KEYUP);



	SetSkill(IdCommands::TurnToLeft, [&]() { m_master->TurnLeft(); });
	SetKeysSkill(IdCommands::TurnToLeft, { SDLK_LEFT, SDLK_a }, SDL_KEYDOWN);

	SetSkill(IdCommands::TurnToRight, [&]() { m_master->TurnRight(); });
	SetKeysSkill(IdCommands::TurnToRight, { SDLK_RIGHT, SDLK_d }, SDL_KEYDOWN);

	SetSkill(IdCommands::ResetDirectionRotation, [&]() { m_master->ResetDirectionRotation(); });
	SetKeysSkill(IdCommands::ResetDirectionRotation, { SDLK_LEFT, SDLK_a, SDLK_RIGHT, SDLK_d }, SDL_KEYUP);


	SetSkill(IdCommands::ChangePlayerCamera, [&]() { m_master->ChangePlayerCamera(); });
	SetKeysSkill(IdCommands::ChangePlayerCamera, { SDLK_v }, SDL_KEYDOWN);

	SetSkill(IdCommands::ChangeWorldCamera, [&]() { m_master->ChangeWorldCamera(); });
	SetKeysSkill(IdCommands::ChangeWorldCamera, { SDLK_b }, SDL_KEYDOWN);


	SetSkill(IdCommands::SwitchFlashLight, [&]() { m_master->SwitchFlashLight(); });
	SetKeysSkill(IdCommands::SwitchFlashLight, { SDLK_SPACE }, SDL_KEYUP);

	SetSkill(IdCommands::Shoot, [&]() { m_master->Shoot(); });
	SetKeysSkill(IdCommands::Shoot, { SDLK_z }, SDL_KEYUP);

}

void CPlayerController::CheckListCommands() const
{
	for (const auto & element : m_listFunctions)
	{
		if (element.second.m_skill == nullptr)
		{
			throw std::runtime_error("No function with id " + std::to_string(short(element.first)));
		}
	}
};
