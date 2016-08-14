#include "stdafx.h"
#include "../stdafx.h"
#include "Player.h"

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
	IdCommands id = FindCommand(event);
	if (id != IdCommands::AmountCommands)
	{
		m_listFunctions[id].m_skill();
	}
}

void CPlayer::CController::OnKeyUp(const SDL_KeyboardEvent & event)
{
	(void)event;
}

void CPlayer::CController::SetSkill(IdCommands id, const std::function<void()> function)
{
	m_listFunctions[id].m_skill = function;
}

void CPlayer::CController::SetKeysSkill(IdCommands id, const CPlayer::KeyList & keys)
{
	m_listFunctions[id].m_keys = keys;
}

CPlayer::CController::IdCommands CPlayer::CController::FindCommand(const SDL_KeyboardEvent & event)
{
	for (const auto & element : m_listFunctions)
	{
		const auto & keys = element.second.m_keys;
		if (std::find(keys.begin(), keys.end(), event.keysym.sym) != keys.end())
		{
			return element.first;
		}
	}

	return IdCommands::AmountCommands;
}

void CPlayer::CController::SetFunctionList()
{
	SetSkill(IdCommands::GoToForward, [&]() { m_master->GoForward(); });
	SetKeysSkill(IdCommands::GoToForward, { SDLK_UP, SDLK_w } );

	SetSkill(IdCommands::GoToBack, [&]() { m_master->GoBack(); });
	SetKeysSkill(IdCommands::GoToBack, {SDLK_DOWN, SDLK_s } );

	SetSkill(IdCommands::TurnToLeft, [&]() { m_master->TurnLeft(); });
	SetKeysSkill(IdCommands::TurnToLeft, { SDLK_LEFT, SDLK_a } );

	SetSkill(IdCommands::TurnToRight, [&]() { m_master->TurnRight(); });
	SetKeysSkill(IdCommands::TurnToRight, { SDLK_RIGHT, SDLK_d } );

	SetSkill(IdCommands::ChangePlayerCamera, [&]() { m_master->ChangePlayerCamera(); });
	SetKeysSkill(IdCommands::ChangePlayerCamera, { SDLK_v });

	SetSkill(IdCommands::ChangeWorldCamera, [&]() { m_master->ChangeWorldCamera(); });
	SetKeysSkill(IdCommands::ChangeWorldCamera, { SDLK_b });
}

void CPlayer::CController::CheckListCommands() const
{
	for (const auto & element : m_listFunctions)
	{
		if (element.second.m_skill == nullptr)
		{
			throw std::runtime_error("No function with id " + std::to_string(short(element.first)));
		}
	}
};
