#pragma once

#include <string>
#include <vector>


#include "Weapon.h"
#include "World\Actor\Shoot\HaveShootTypes.h"

class CWorld;

class CHaveWeaponTypes
	: public CHaveShootTypes
{
public:
	CHaveWeaponTypes();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	using ArrayWeaponTypes = std::array<CWeaponType, size_t(WeaponTypeSpace::AMOUNT_TYPES)>;

	const CWeaponType*				GetWeaponType(const WeaponTypeSpace::Id index) const;

protected:
	void							SetWeaponType(size_t index
												, const int damage
												, const float timeReload
												, const CShootType & shootType
												, const float velocity
												, const float distanse);// TODO : see need there something
															   //////////////////////////////////////////////////////////////////////
															   // Data
protected:
	ArrayWeaponTypes					m_weaponTypes;
};