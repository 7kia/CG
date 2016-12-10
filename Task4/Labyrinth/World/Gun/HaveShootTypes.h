#pragma once

#pragma once

#include "Shoot.h"
#include <string>

class CHaveShootTypes
{
public:
	CHaveShootTypes();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	using ArrayShootTypes = std::array<CShootType, size_t(ShootTypeSpace::AMOUNT_TYPES)>;

	void							CreateShootTypes();
	const CShootType*				GetShootType(size_t index) const;
private:
	void							SetShootType(size_t index);// TODO : see need there something
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	ArrayShootTypes					m_shootTypes;
};