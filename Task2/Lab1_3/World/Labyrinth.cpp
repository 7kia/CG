#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"
#include "WeldVertexes.h"

#include <algorithm>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>

CLabyrinthLevel::CLabyrinthLevel()
	: CIdentity3DShape()
{
}

void CLabyrinthLevel::AddWall(PWall pWall)
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
					return source + uint32_t(m_indexCount) * 4;
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

void CLabyrinthLevel::ReallocateMemory()
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

CLabyrinth::CLabyrinth()
{
	const size_t amountLevels = 3;
	m_shapes.reserve(amountLevels);

	for (size_t index = 0; index < amountLevels; ++index)
	{
		m_shapes.push_back(std::make_shared<CLabyrinthLevel>());
	}
}

void CLabyrinth::AddWall(PWall pWall, size_t index)
{
	dynamic_cast<CLabyrinthLevel*>(m_shapes[index].get())->AddWall(pWall);
}

void CLabyrinth::ReallocateMemory()
{
	for (auto & level : m_shapes)
	{
		dynamic_cast<CLabyrinthLevel*>(level.get())->ReallocateMemory();
	}
}
