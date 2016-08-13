#pragma once

#include "Player.h"

class CHavePlayer
{
public:
	CHavePlayer();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	CAbcstartCamera*				GetCamera();

	void							SetSpawnPoint(const glm::vec3 & position);
	glm::vec3						GetSpawnPoint() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	CPlayer							m_player;
	glm::vec3						m_spawnPoint;


};