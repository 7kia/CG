#pragma once

#include <memory>
#include <Box2D\Box2D.h>

class ContactListener : public b2ContactListener
{

	void BeginContact(b2Contact* contact);
};

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
	ContactListener					m_contactListener;
};