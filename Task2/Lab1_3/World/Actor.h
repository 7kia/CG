#pragma once

#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"


class IActor
	: public IDrawable
	, public IUpdatable
{
public:
	virtual ~IActor() = default;
};