#pragma once

#include "Mixin/Drawable.h"
#include "Mixin/Updatable.h"
#include "IsDeletable.h"
#include <memory>

class CActor
	: public IDrawable
	, public IUpdatable
	, public CIsDeletable
{
public:
	enum class idClass
	{
		None = 0
		, World
		, Map
		, Wall
		, LifeObject
		, Shoot
	};

	CActor(idClass id);
	virtual ~CActor() = default;

	idClass			GetIdClass() const;
protected:
	idClass			m_idClass = idClass::None;
};

using IActorSharedPtr = std::shared_ptr<CActor>;