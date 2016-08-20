#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"
#include "WeldVertexes.h"

#include <algorithm>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>

CLabyrinth::CLabyrinth()
	: CIdentity3DShape()
{
}

void CLabyrinth::AddWall(PWall pWall)
{
	auto visual = pWall->GetVisual();
	for (size_t index = 0; index < visual->GetAmountShapes(); ++index)
	{
		if (pWall->GetVisible(index))
		{
			auto currentRectangle = dynamic_cast<C3DRectangle*>(visual->GetShape(index).get());

			auto vertexes = currentRectangle->GetVertexes();

			////////////////////////////////////
			// Search common vertexes
			VectorPairsIndexes replaceIndexes = FindCommonVertexes(m_vertices, vertexes);

			if (true)//!WeldToFirst(this, currentRectangle, replaceIndexes))//
			{

				auto indexes = currentRectangle->GetIndexes();

				auto append = [&](uint32_t source) {
					return source + m_indexCount * 4;
				};
				boost::transform(indexes, indexes.begin(), append);

				m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());
				m_indicies.insert(m_indicies.end(), indexes.begin(), indexes.end());

			}
			
			////////////////////////////////////
			


			++m_indexCount;
		}
	}

}

void CLabyrinth::ReallocateMemory()
{
	auto vertexes = m_vertices;
	auto indexes = m_indicies;

	m_vertices.clear();
	m_vertices.reserve(vertexes.size());
	m_vertices = vertexes;

	m_indicies.clear();
	m_indicies.reserve(indexes.size());
	m_indicies = indexes;

}
