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
			auto indexes = currentRectangle->GetIndexes();

			auto append = [&](uint32_t source) {
				return source + uint32_t(m_indexCount);
			};
			boost::transform(indexes, indexes.begin(), append);

			m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());
			m_indicies.insert(m_indicies.end(), indexes.begin(), indexes.end());

			m_indexCount += currentRectangle->GetAmountVertexes();
		}
	}

}

void CLabyrinthLevel::ShrinkToFit()
{
	m_vertices.shrink_to_fit();
	m_indicies.shrink_to_fit();
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

void CLabyrinth::ShrinkToFit()
{
	for (auto & level : m_shapes)
	{
		dynamic_cast<CLabyrinthLevel*>(level.get())->ShrinkToFit();
	}
}
