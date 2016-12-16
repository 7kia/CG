#pragma once

#include "Mixin/Drawable.h"
#include "Mixin/Updatable.h"
#include "IsDeletable.h"
#include "Faction.h"
#include <memory>

class CActor
	: public IDrawable
	, public IUpdatable
	, public CIsDeletable
	, public CHaveFaction
{
public:
	enum class IdClass
	{
		None = 0
		, World
		, Map
		, Wall
		, LifeObject
		, Shoot
		, AmountClasses
	};

	CActor(IdClass id);
	virtual ~CActor() = default;

	IdClass			GetIdClass() const;

protected:
	IdClass			m_idClass = IdClass::None;
};

using ActorSharedPtr = std::shared_ptr<CActor>;