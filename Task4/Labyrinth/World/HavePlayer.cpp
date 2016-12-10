#include "stdafx.h"
#include "HavePlayer.h"

CHavePlayer::CHavePlayer()
{
}

CAbcstartCamera* CHavePlayer::GetCamera()
{
	return m_player.GetCamera();
}

void CHavePlayer::SetSpawnPoint(const glm::vec3 & position)
{
	m_spawnPoint = position;
}

glm::vec3 CHavePlayer::GetSpawnPoint() const
{
	return m_spawnPoint;
}
