#include "stdafx.h"
#include "Faction.h"

CHaveFaction::CHaveFaction()
{
}

void CHaveFaction::SetIdFaction(IdFaction id)
{
	m_idFaction = id;
}

IdFaction CHaveFaction::GetIdFaction() const
{
	return m_idFaction;
}
