#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: IActor(IActor::idClass::World)
	, IInputEventAcceptor()
	, CHaveLifeObjects()
	, CHaveWallTypes()
	, CHavePhysicalWorld()
	, CHavePlayer()
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

	m_player->Draw();// GetPlayer() not work, see can solve the problem

	m_wallTypes[0].GetTexture()->DoWhileBinded([&] {	
		m_map.Draw();
	});

	for (auto & shoot : m_shoots)
	{
		shoot->Draw();
	}
}

void CWorld::Update(float deltaTime)
{
	GetPlayer()->Update(deltaTime);

	m_map.Update(deltaTime);

	for (auto shoot : m_shoots)
	{
		shoot->Update(deltaTime);
	}

	m_world->Step(deltaTime, 8, 3);
}

void CWorld::CreateScene()
{
	CreateWallTypes();
	m_map.Create("Resources\\map.bmp", this);
	CreatePlayer(m_spawnPoint, PlayerSpace::PLAYER_DIRECTION);

	/*// TODO : delete it
	CreateShoot(glm::vec3(-16.f, 0.5f, -16.f)
		, glm::vec3(1.f, 0.f, 0.f)
		, GetShootType(ShootTypeSpace::Id::Player)
		,
		);
	*/
	
}

void CWorld::CreatePlayer(const glm::vec3 & position
							, const glm::vec3 & direction)
{
	m_lifeObjects.push_back(std::move(std::make_unique<CPlayer>(position
									, direction
									, GetLifeObjectType(CLifeObjectType::Id::Player)
									, this))
							);

	m_player = dynamic_cast<CPlayer*>(m_lifeObjects[0].get());// TODO :  fix convertation

	if (position == glm::vec3())
	{
		throw std::runtime_error("Player position not define");
	}
}

void CWorld::CreateShoot(const glm::vec3 & position
	, const glm::vec3 & direction
	, const CWeapon & weapon
	)
{
	m_shoots.push_back(std::make_shared<CShoot>(position
		, direction
		, weapon
		, this));
}