#pragma once

enum class IdFaction
{
	None = 0
	, Player
	, Enemy
	, AmountFactions
};


class CHaveFaction
{
public:
	CHaveFaction();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			SetIdFaction(IdFaction id);
	IdFaction		GetIdFaction() const;
protected:
	IdFaction		m_idFaction = IdFaction::None;
};
