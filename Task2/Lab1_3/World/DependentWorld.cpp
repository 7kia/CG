#include "stdafx.h"
#include "World.h"


unsigned CMap::GetIndexWallType(int heigth)
{
	switch (heigth)
	{
	case -1: case 1:
		return unsigned(CHaveWallTypes::IdWallType::Plank);
	case 0:
		return unsigned(CHaveWallTypes::IdWallType::Break);
	default:
		throw std::runtime_error("Incorrect index");
		break;
	}
}

void CMap::AddWall(size_t x, size_t y, int z)
{
	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_unique<CWallView>();
	pWall->SetType(pWorld->GetWallType(GetIndexWallType(z)));

	for (int xShift = -1; xShift <= 1; ++xShift)
	{
		for (int yShift = -1; yShift <= 1; ++yShift)// this and high for process around wall
		{
			for (int zShift = -1; zShift <= 1; ++zShift)
			{

				if (abs(xShift) != abs(yShift))// not process itself
				{
					ProcessLateralEdge(pWall.get(), glm::vec3(x, y, z), glm::vec3(xShift, yShift, zShift));
				}
				else if ((xShift == 0) && (yShift == 0))
				{
					ProcessVerticalEdge(pWall.get(), glm::vec3(x, y, z), zShift);
				}

			}
		}
	}


	pWall->SetTransform(glm::translate(glm::mat4(), { xPosition, z * WallSpace::SIZE, yPosition }));

	m_walls.emplace_back(std::move(pWall));
}
