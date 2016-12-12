#pragma once

#include "Player.h"

class CWorld;

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

	CPlayer*						GetPlayer();
//////////////////////////////////////////////////////////////////////
// Data
protected:
	CPlayer*						m_player = nullptr;
	glm::vec3						m_spawnPoint;


};