#pragma once

#include <vector>
#include "Gun\Shoot.h"

class CWorld;

class CHaveShoots
{
public:
	CHaveShoots();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//void							SetSpawnPoint(const glm::vec3 & position);
	//glm::vec3						GetSpawnPoint() const;

	void							CreateShoot(const glm::vec3 & position
												, const glm::vec3 & direction
												, const CShootType &type
												, CWorld* pWorld);

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	std::vector<CShoot>				m_shoots;


};