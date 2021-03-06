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

static bool ProcessContactShootAndWall(void* userDataA, void* userDataB)
{
	if (userDataA == nullptr)
	{
		CActor* actorBData = static_cast<CActor*>(userDataB);
		auto typeB = actorBData->GetIdClass();

		if (typeB == CActor::IdClass::Shoot)
		{
			actorBData->SetStateLive(false);
			return true;
		}
	}
	return false;
}

static bool ProcessOtherContact(CActor::IdClass typeA
	, CActor::IdClass typeB
	, void* userDataA
	, void* userDataB)
{
	if (typeA == CActor::IdClass::Shoot)//
	{
		CShoot* shoot = static_cast<CShoot*>(userDataA);
		////////////////////
		// Shoot destroy
		if (typeB == CActor::IdClass::Shoot)
		{

			CShoot* secondShoot = static_cast<CShoot*>(userDataB);
			shoot->AddHealth(-secondShoot->GetDamage());
			secondShoot->AddHealth(-secondShoot->GetDamage());
			return true;
		}
		////////////////////
		else if (typeB == CActor::IdClass::LifeObject)
		{
			CLifeObject* lifeObject = static_cast<CLifeObject*>(userDataB);

			shoot->SetStateLive(false);
			lifeObject->AddHealth(-shoot->GetDamage());
			return true;
		}
	}
	return false;
}

void ContactListener::BeginContact(b2Contact* contact) {


	void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if ((userDataA == nullptr) && (userDataB == nullptr)
		&& (userDataA == userDataB))
	{
		return;
	}

	if (ProcessContactShootAndWall(userDataA, userDataB))
	{
		return;
	}
	if (ProcessContactShootAndWall(userDataB, userDataA))
	{
		return;
	}

	if ((userDataA == nullptr) || (userDataB == nullptr))
	{
		return;
	}

	CActor* actorAData = static_cast<CActor*>(userDataA);
	CActor* actorBData = static_cast<CActor*>(userDataB);

	auto typeA = actorAData->GetIdClass();
	auto typeB = actorBData->GetIdClass();

	if (!ProcessOtherContact(typeA, typeB, userDataA, userDataB))
	{
		ProcessOtherContact(typeB, typeA, userDataB, userDataA);
	}
}