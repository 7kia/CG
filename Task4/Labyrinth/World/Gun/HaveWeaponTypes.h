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
	using ArrayWeaponTypes = std::array<CWeaponType, size_t(CWeaponType::Id::AmountTypes)>;

	const CWeaponType*				GetWeaponType(const CWeaponType::Id index) const;

protected:
	void							SetWeaponType(CWeaponType::Id typeIndex
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