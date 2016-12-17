#pragma once

#include "World/Actor/HaveHealth.h"
#include "World/Actor/Faction.h"

#include "Mixin/Material/HaveTexture.h"
#include <array>


class CShootType
	: public CHaveTexture
	, public CHaveFaction
{
public:
	CShootType();

	enum class Id
	{
		None = -1
		, Player = 0
		, Enemy
		, AmountTypes
	};
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void					SetHealth(int value);// TOOD : see can it mix
	int						GetHealth() const;

	void					SetId(Id id);
	Id						GetId() const;

private:

//////////////////////////////////////////////////////////////////////
// Data
private:
	CStaticFeature					m_health;
	Id								m_id = Id::None;

};