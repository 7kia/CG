#include "stdafx.h"
#include "HavePhysicalWorld.h"

CHavePhysicalWorld::CHavePhysicalWorld()
{
	m_world = std::make_shared<b2World>(b2Vec2(0.0f, 0.f));

	m_world->SetContactListener(&m_contactListener);
}

b2World * CHavePhysicalWorld::GetWorld()
{
	return m_world.get();
}
