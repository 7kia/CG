#include "stdafx.h"
#include "HavePlayer.h"
#include "World\World.h"

CHavePlayer::CHavePlayer()
{
}

CAbcstartCamera* CHavePlayer::GetCamera()
{
	return GetPlayer()->GetCamera();
}

void CHavePlayer::SetSpawnPoint(const glm::vec3 & position)
{
	m_spawnPoint = position;
}

glm::vec3 CHavePlayer::GetSpawnPoint() const
{
	return m_spawnPoint;
}

CPlayer * CHavePlayer::GetPlayer()
{
	return m_player;
}
