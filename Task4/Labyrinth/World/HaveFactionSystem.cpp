#include "stdafx.h"
#include "HaveFactionSystem.h"

CHaveFactionSystem::CHaveFactionSystem()
{
	size_t maxIndex = size_t(IdFaction::AmountFactions);
	for (size_t index = 0; index < maxIndex; ++index)
	{
		m_factionMap.emplace(std::pair<size_t, std::vector<ActorSharedPtr>>(index, std::vector<ActorSharedPtr>()));
	}

}

void CHaveFactionSystem::AddActorToFactionMap(ActorSharedPtr addActor)
{
	m_factionMap[size_t(addActor->GetIdFaction())].push_back(addActor);
}

void CHaveFactionSystem::DeleteFromFactionMapActor(ActorSharedPtr addActor)
{
	size_t indexFaction = size_t(addActor->GetIdFaction());

	auto iterDelete = std::find(m_factionMap[indexFaction].begin(), m_factionMap[indexFaction].end(), addActor);

	if (iterDelete != m_factionMap[indexFaction].end())
	{
		m_factionMap[indexFaction].erase(iterDelete);
	}
	else
	{
		throw std::runtime_error("The entity not content to faction map");
	}
}
