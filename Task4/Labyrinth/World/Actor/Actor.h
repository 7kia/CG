#pragma once

#include "Mixin/Drawable.h"
#include "Mixin/Updatable.h"
#include <memory>

class IActor
	: public IDrawable
	, public IUpdatable
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

	IActor(idClass id);
	virtual ~IActor() = default;

	idClass			GetIdClass() const;
protected:
	idClass			m_idClass = idClass::None;
};

static bool IsShootOrLifeObject(IActor::idClass id)
{
	return (id == IActor::idClass::LifeObject) || (id == IActor::idClass::Shoot);
};

using IActorSharedPtr = std::shared_ptr<IActor>;