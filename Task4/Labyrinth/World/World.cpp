#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: IActor()
	, IInputEventAcceptor()
	, CHaveWeaponTypes()
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
	m_player.m_pController->OnKeyDown(event);
}

void CWorld::OnKeyUp(const SDL_KeyboardEvent & event)
{
	m_player.m_pController->OnKeyUp(event);
}

void CWorld::Draw() const
{
	m_material.Setup();

	m_player.Draw();

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
	m_player.Update(deltaTime);

	m_map.Update(deltaTime);

	for (auto shoot : m_shoots)
	{
		shoot->Update(deltaTime);
	}

	m_world->Step(deltaTime, 8, 3);
}

void CWorld::CreateScene()
{
	CreateWeaponTypes();
	CreateWallTypes();
	m_map.Create("Resources\\map.bmp", this);
	CreatePlayer(m_spawnPoint, PlayerSpace::PLAYER_DIRECTION);

	CreateShoot(glm::vec3(-13.f, 0.5f, -7.f)
		, glm::vec3(1.f, 0.f, 0.f)
		, GetShootType(ShootTypeSpace::Id::Player)
		, this);
}

void CWorld::CreatePlayer(const glm::vec3 & position
							, const glm::vec3 & direction)
{
	if (position == glm::vec3())
	{
		throw std::runtime_error("Player position not define");
	}


	m_player.CreatePlayer(position
						, direction
						, this
						, TextureSpace::TexturePaths[size_t(TextureSpace::Id::Player)]);
}

void CWorld::CreateShoot(const glm::vec3 & position
	, const glm::vec3 & direction
	, const CShootType & type
	)
{
	m_shoots.push_back(std::make_shared<CShoot>(position, direction, type, world));
}