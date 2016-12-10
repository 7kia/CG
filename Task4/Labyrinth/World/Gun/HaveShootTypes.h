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

	void							CreateShootTypes();
	const CShootType*				GetShootType(const ShootTypeSpace::Id index) const;

protected:
	void							SetShootType(size_t index);// TODO : see need there something
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	ArrayShootTypes					m_shootTypes;
};