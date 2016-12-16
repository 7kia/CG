#pragma once

#include <string>
#include <vector>

#include "Shoot.h"


class CWorld;

class CHaveShootTypes
{
public:
	CHaveShootTypes();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	using ArrayShootTypes = std::array<CShootType, size_t(ShootTypeSpace::AMOUNT_TYPES)>;

	const CShootType&				GetShootType(const ShootTypeSpace::Id index) const;

protected:
	void							SetShootType(size_t index
												, IdFaction idFaction
												, const std::string & texturePath
												, int health);// TODO : see need there something
//////////////////////////////////////////////////////////////////////
// Data
protected:
	ArrayShootTypes					m_shootTypes;
};