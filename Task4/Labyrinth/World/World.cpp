#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: CActor(CActor::IdClass::World)
	, IInputEventAcceptor()
	, CHaveLifeObjects()
	, CHaveWallTypes()
	, CHavePhysicalWorld()
	, CHavePlayer()
	, CHaveFactionSystem()
{
	m_material.SetAmbient(WorldSpace::GRAY_RGBA);
	m_material.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_material.SetSpecular(WorldSpace::FADED_WHITE_RGBA);
	m_material.SetShininess(WorldSpace::MATERIAL_SHININESS);
}

void CWorld::OnKeyDown(const SDL_KeyboardEvent & event)
{
	GetPlayer()->m_pController.OnKeyDown(event);
}

void CWorld::OnKeyUp(const SDL_KeyboardEvent & event)
{
	GetPlayer()->m_pController.OnKeyUp(event);
}

void CWorld::Draw() const
{
	m_material.Setup();

	// TODO : fix bind texture
	m_wallTypes[0].GetTexture()->DoWhileBinded([&] {	
		m_map.Draw();
	});

	for (auto & actor : m_actors)
	{
		actor->Draw();
	}
}

void CWorld::Update(float deltaTime)
{
	if (m_play)
	{
		UpdateBehavior();

		m_map.Update(deltaTime);

		for (auto actor : m_actors)
		{
			actor->Update(deltaTime);
		}

		DeleteDeathObject();
		m_world->Step(deltaTime, 8, 3);
	}
}

void CWorld::SwitchPlayState()
{
	m_play = !m_play;
}

void CWorld::CreateScene()
{
	CreateWallTypes();
	m_map.Create("Resources\\map.bmp", this);
	CreatePlayer(m_spawnPoint, PlayerSpace::PLAYER_DIRECTION);
	
	CreateLifeObject(CLifeObjectType::Enemy, glm::vec3(-10.f, 0.f, -10.f), glm::vec3());

}

void CWorld::CreatePlayer(const glm::vec3 & position
							, const glm::vec3 & direction)
{
	m_player = dynamic_cast<CPlayer*>(CreateLifeObject(CLifeObjectType::Player
														, position
														, direction).get());// TODO :  fix convertation
}

ActorSharedPtr CWorld::CreateLifeObject(CLifeObjectType::Id id
											, const glm::vec3 & position
											, const glm::vec3 & direction)
{

	if (position == glm::vec3())
	{
		throw std::runtime_error("LifeObject position not define");
	}

	LifeObjectSharedPtr lifeObject;
	switch (id)
	{
		break;
	case CLifeObjectType::Player:
		lifeObject = std::make_shared<CPlayer>(GetLifeObjectType(id)
												, this	
												, position
												, direction
												);
		AddActorToFactionMap(lifeObject);
		break;
	case CLifeObjectType::Enemy:
		lifeObject = std::make_shared<CLifeObject>(GetLifeObjectType(id)
													, this
													, position
													, direction
													);
		break;
	case CLifeObjectType::None:
	case CLifeObjectType::AmountIDs:
	default:
		throw std::runtime_error("LifeObject type not define");
		break;
	}

	m_lifeObjects.push_back(lifeObject);
	AddActorToFactionMap(lifeObject);
	m_actors.push_back(lifeObject);

	return lifeObject;
}

void CWorld::DeleteDeathObject()
{
	for (size_t index = m_actors.size(); index > 0; --index)
	{
		size_t resultIndex = index - 1;
		if (!m_actors[resultIndex]->IsLive())
		{
			DeleteFromFactionMapActor(m_actors[resultIndex]);
			m_actors.erase(m_actors.begin() + resultIndex);
		}
	}
};

void CWorld::CreateShoot(const glm::vec3 & position
	, const glm::vec3 & direction
	, const CWeapon & weapon
	)
{
	std::shared_ptr<CShoot> addShoot = std::make_shared<CShoot>(position
																, direction
																, weapon
																, this);
	AddActorToFactionMap(addShoot);
	m_actors.push_back(addShoot);
}

// TODO : tranfser to other place
void CWorld::UpdateBehavior()// TODO : redefine
{
	glm::vec3 positionPlayer = GetPlayer()->GetPosition();
	for (auto &object : m_lifeObjects)
	{
		if (object->GetIdType() != CLifeObjectType::Id::Player)
		{
			float distanse = glm::distance(positionPlayer, object->GetPosition());// positionPlayer.getDistance(object->getPosition());
			if (distanse < object->GetVisionRange())
			{
				object->SetDirection(GetDirectionToObject(*object.get(), *GetPlayer()));
				//DefineDirectionToEnemyForObject(object, positionPlayer);
				DefineNeedAttackEnemy(*object.get(), *GetPlayer());
			}
		}
	}

}

glm::vec3 CWorld::GetDirectionToObject(CHave3DPosition & to, CHave3DPosition & from)
{
	const glm::vec3 direction = to.GetPosition() - from.GetPosition();

	return glm::normalize(direction);
}

void CWorld::DefineNeedAttackEnemy(CLifeObject & object, CLifeObject & enemy)
{
	float distanse = glm::distance(enemy.GetPosition(), object.GetPosition());
	float distanceAttack = object.GetDistanceWeapon();

	if (distanse < distanceAttack)
	{
		object.SetState(CLifeObject::StateId::Attack);
	}
	else
	{
		object.SetState(CLifeObject::StateId::Move);

		//object->ResetWeapon();
	}
}