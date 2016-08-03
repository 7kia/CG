#pragma once

class IUpdatable
{
public:
	virtual	~IUpdatable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void Update(float deltaTime) { (void)deltaTime; };
};