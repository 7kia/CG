#pragma once

class IAdvancable
{
public:
	virtual ~IAdvancable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void		Advance(float dt) = 0;
};