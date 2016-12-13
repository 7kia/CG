#pragma once

#include "World/Actor/HaveHealth.h"

#include "Mixin/Material/HaveTexture.h"
#include <array>


namespace ShootTypeSpace
{
	enum class Id
	{
		Player = 0
		, Enemy
		, AmountTypes
	};


	const unsigned AMOUNT_TYPES = unsigned(Id::AmountTypes);


};

class CShootType
	: public CHaveTexture
{
public:
	CShootType();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetHealth(int value);// TOOD : see can it mix
	int						GetHealth() const;


private:

//////////////////////////////////////////////////////////////////////
// Data
private:
	CStaticFeature					m_health;

};