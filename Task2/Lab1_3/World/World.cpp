#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: IActor()
	, IInputEventAcceptor()
	, CHaveWallTypes()
	, CHavePhysicalWorld()
	, CHavePlayer()
	, m_sunlight(GL_LIGHT0)
{
	m_material.SetAmbient(WorldSpace::WHITE_RGBA);
	m_material.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_material.SetSpecular(WorldSpace::FADED_WHITE_RGBA);
	m_material.SetShininess(WorldSpace::MATERIAL_SHININESS);

	m_sunlight.SetDirection(WorldSpace::SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_sunlight.SetAmbient(0.f * WorldSpace::WHITE_RGBA);
	m_sunlight.SetSpecular(WorldSpace::WHITE_RGBA);
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
	m_sunlight.Setup();
	m_material.Setup();

	m_player.Draw();

	// TODO : без текстурировния лабиринта не работают коллизии
	m_wallTypes[0].GetTexture()->DoWhileBinded([&] {	
		m_map.Draw();
	});
}

void CWorld::Update(float deltaTime)
{
	m_player.Update(deltaTime);

	m_map.Update(deltaTime);

	m_world->Step(deltaTime, 8, 3);
}

void CWorld::CreateScene()
{
	CreateWallTypes();
	m_map.Create("Resources\\map.bmp", this);
	CreatePlayer(m_spawnPoint, PlayerSpace::PLAYER_DIRECTION);

}

void CWorld::CreatePlayer(const glm::vec3 & position
							, const glm::vec3 & direction)
{
	if (position == glm::vec3())
	{
		throw std::runtime_error("Player position not define");
	}

	m_player.CreatePlayer(position, direction, this);
	m_player.SetTexture(TextureSpace::TexturePaths[1]);
}
