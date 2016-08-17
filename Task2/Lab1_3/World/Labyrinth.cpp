#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"

CLabyrinth::CLabyrinth()
	: CIdentity3DShape()
{
}

void CLabyrinth::BuildLabyrinth(const std::vector<PWall> & walls)
{
	for (const auto & wall : walls)
	{
		auto visual = wall->GetVisual();
		for (size_t index = 0; index < visual->GetAmountShapes(); ++index)
		{
			auto currentRectangle = dynamic_cast<C3DRectangle*>(visual->GetShape(index).get());
			for (size_t indexTriangles = 0; indexTriangles < currentRectangle->GetAmountShapes(); ++indexTriangles)
			{
				auto currentTriangle = dynamic_cast<C3DTriangle*>(currentRectangle->GetShape(indexTriangles).get());

				auto vertexes = currentTriangle->GetVertexes();
				auto indexes = currentTriangle->GetIndexes();
				m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());
				m_indicies.insert(m_indicies.end(), indexes.begin(), indexes.end());
			}
		}


	}
}
