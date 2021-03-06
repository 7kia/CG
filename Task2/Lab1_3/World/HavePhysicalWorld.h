#pragma once

#include <memory>
#include <Box2D\Box2D.h>

class CHavePhysicalWorld
{
public:
	CHavePhysicalWorld();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	b2World*						GetWorld();// must be not constant
//////////////////////////////////////////////////////////////////////
// Data
public:
	std::shared_ptr<b2World>		m_world;
};