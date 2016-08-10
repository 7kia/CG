#include "stdafx.h"
#include "World.h"

void CMap::AddWall(unsigned x, unsigned y, int z)
{
	float xPosition = WallSpace::SIZE * x - m_centerMap.x;
	float yPosition = WallSpace::SIZE * y - m_centerMap.y;

	auto pWall = std::make_unique<CWall>();
	pWall->SetType(pWorld->GetWallType(1));

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


	auto pTransform = std::make_unique<CTransformShapeDecorator>();
	pTransform->SetChild(std::move(pWall));
	pTransform->SetTransform(glm::translate(glm::mat4(), { xPosition, z * WallSpace::SIZE, yPosition }));

	m_walls.emplace_back(std::move(pTransform));
}
