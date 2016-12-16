#pragma once

#include <vector>
#include <unordered_map>

#include "World\Actor\LifeObjects\LifeObjects.h"
#include "World\Actor\Player\Player.h"

class CHaveFactionSystem
{
public:
	CHaveFactionSystem();
	using FactionMap = std::unordered_map<size_t, std::vector<ActorSharedPtr>>;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		AddActorToFactionMap(ActorSharedPtr addActor);
	void		DeleteFromFactionMapActor(ActorSharedPtr addActor);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	FactionMap m_factionMap;
};