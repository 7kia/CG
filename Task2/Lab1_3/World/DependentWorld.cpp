// TODO: remove this file, merge it with Map.cpp

#include "stdafx.h"
#include "../stdafx.h"
#include <Box2D\Box2D.h>
#include "World.h"

unsigned CMap::GetIndexWallType(const glm::vec3 & position
								, size_t length
								, size_t width)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int heigth = int(position.z);
	switch (heigth)
	{
	case -1: case 1:
		return unsigned(CHaveWallTypes::IdWallType::Plank);
	case 0:
		if ((x == 0) || (x == length - 1)
			|| (y == 0) || (y == width - 1))
		{
			return unsigned(CHaveWallTypes::IdWallType::Arch);
		}
		return unsigned(CHaveWallTypes::IdWallType::Break);
	default:
		throw std::runtime_error("Incorrect index");
		break;
	}
}

bool CMap::WallHaveCollision(int heigth)
{
	switch (heigth)
	{
		// TODO: create enum with list of height values as constants
	case -1: case 1: // TODO: what is -1? what is 1?
		return false;
	case 0: // TODO: what is 0?
		return true;
	default:
		throw std::runtime_error("Incorrect index");
	}
}

void CMap::AddWall(const glm::vec3 & position
					, size_t length
					, size_t width)
{
	size_t x = size_t(position.x);
	size_t y = size_t(position.y);
	int z = int(position.z);

	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_unique<CWall>();
	pWall->SetType(pWorld->GetWallType(GetIndexWallType(position, length, width)));
	
	for (int xShift = -1; xShift <= 1; ++xShift)
	{
		for (int yShift = -1; yShift <= 1; ++yShift)// this loop and high for process around wall
		{
			for (int zShift = -1; zShift <= 1; ++zShift)
			{

				if (abs(xShift) != abs(yShift))// not process itself
				{
					ProcessLateralEdge(pWall.get(), position, glm::vec3(xShift, yShift, zShift));
				}
				else if ((xShift == 0) && (yShift == 0))
				{
					ProcessVerticalEdge(pWall.get(), position, zShift);
				}

			}
		}
	}

	// SetPosition duplicate because before call AddToWorld must set position
	pWall->SetPosition(glm::vec3(xPosition, z * WallSpace::SIZE, yPosition));
	pWall->SetHaveCollision(WallHaveCollision(z));

	if (pWall->GetHaveCollision())
	{
		pWall->SetPosition(glm::vec3(xPosition, z * WallSpace::SIZE, yPosition));
		pWall->AddToWorld(pWorld->GetWorld());
	}
	m_walls.emplace_back(std::move(pWall));
}

void CMap::AddPlayer(const glm::vec3 & position)
{
	float xPosition = WallSpace::SIZE * position.x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * position.y - m_centerMap.y;

	pWorld->SetSpawnPoint(glm::vec3(xPosition, yPosition, position.z * WallSpace::SIZE));
}

void CPlayer::SetCollison()
{
	m_collision.SetRadius(1.f);
	m_collision.SetReferenceSystemOrigin(glm::vec2());

	auto position = GetCamera()->GetPosition();
	m_collision.SetPosition(position.x, position.y);
	m_collision.SetVelocity(glm::vec2());


	m_visual.SetType(m_pWorld->GetWallType(0));
	m_visual.SetTransform(glm::translate(glm::mat4(), position));

	m_collision.AddToWorld(m_pWorld->GetWorld());
}

void CPlayer::SetWorld(CWorld * pWorld)
{
	m_pWorld.reset(pWorld);
}

void CPlayer::CreatePlayer(const glm::vec3 & position
							, const glm::vec3 & direction
							, CWorld* pWorld)
{
	m_collision.SetPVisual(&m_visual);

	SetCameras();

	GetCamera()->SetPosition(position);
	GetCamera()->SetDirection(direction);

	SetWorld(pWorld);
	SetCollison();

	m_flashlight.SetPosition(position);
	m_flashlight.SetDiffuse(PlayerSpace::WHITE_RGBA);
	m_flashlight.SetAmbient(0.1f * PlayerSpace::WHITE_RGBA);
	m_flashlight.SetSpecular(PlayerSpace::WHITE_RGBA);
}
