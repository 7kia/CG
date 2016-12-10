#pragma once

#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"
#include <memory>

class IActor
	: public IDrawable
	, public IUpdatable
{
public:
	virtual ~IActor() = default;
};

using IActorUniquePtr = std::unique_ptr<IActor>;