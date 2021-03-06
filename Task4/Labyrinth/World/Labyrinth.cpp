#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"

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

			const uint32_t indexOffset = uint32_t(m_vertices.size());
			boost::transform(currentRectangle->GetIndexes(), std::back_inserter(m_indicies), [&](uint32_t source) {
				return source + indexOffset;
			});
			m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());
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
