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
	using ArrayShootTypes = std::array<CShootType, size_t(CShootType::Id::AmountTypes)>;

	const CShootType&				GetShootType(const CShootType::Id index) const;

protected:
	void							SetShootType(CShootType::Id typeIndex
												, IdFaction idFaction
												, const std::string & texturePath
												, int health);// TODO : see need there something
//////////////////////////////////////////////////////////////////////
// Data
protected:
	ArrayShootTypes					m_shootTypes;
};