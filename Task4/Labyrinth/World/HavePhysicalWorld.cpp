#include "stdafx.h"
#include "HavePhysicalWorld.h"
#include "World\World.h"

CHavePhysicalWorld::CHavePhysicalWorld()
{
	m_world = std::make_shared<b2World>(b2Vec2(0.0f, 0.f));

	m_world->SetContactListener(&m_contactListener);
}

b2World * CHavePhysicalWorld::GetWorld()
{
	return m_world.get();
}


void ContactListener::BeginContact(b2Contact* contact) {


	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if ((userDataA == nullptr) || (userDataB == nullptr))
	{
		return;
	}
// TODO
		IActor* actorAData = static_cast<IActor*>(userDataA);
		IActor* actorBData = static_cast<IActor*>(userDataB);

		auto typeA = actorAData->GetIdClass();
		auto typeB = actorBData->GetIdClass();

		//if (IsShootOrLifeObject(typeA) || IsShootOrLifeObject(typeB))
		//{
			if (typeA == IActor::idClass::Shoot)//
			{
				CShoot* shoot = static_cast<CShoot*>(userDataA);
				////////////////////
				// Shoot destroy
				if (typeB == IActor::idClass::Shoot)
				{
					
					CShoot* secondShoot = static_cast<CShoot*>(userDataB);
					shoot->AddHealth(-shoot->GetMaxHealth());
					secondShoot->AddHealth(-secondShoot->GetMaxHealth());
				}
				////////////////////
				else if (typeB == IActor::idClass::LifeObject)
				{
					CLifeObject* lifeObject = static_cast<CLifeObject*>(userDataB);

					shoot->AddHealth(-shoot->GetMaxHealth());
					lifeObject->AddHealth(-shoot->GetDamage());
				}
			}
		//}
	/*

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	{
	static_cast<Ball*>(bodyUserData)->startContact();

	}

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	{
	static_cast<Ball*>(bodyUserData)->startContact();

	}
	*/


}

// TOOD: see need it
void ContactListener::EndContact(b2Contact* contact) {

	/*
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
	static_cast<Ball*>(bodyUserData)->endContact();

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
	static_cast<Ball*>(bodyUserData)->endContact();
	*/


}