#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"
#include <algorithm>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>

CLabyrinth::CLabyrinth()
	: CIdentity3DShape()
{
}

void CLabyrinth::BuildLabyrinth(const std::vector<PWall> & walls)
{
	size_t countVertex = 0;
	size_t countIndexes = 0;
	size_t indexCount = 0;
	for (const auto & wall : walls)
	{
		auto visual = wall->GetVisual();
		for (size_t index = 0; index < visual->GetAmountShapes(); ++index)
		{
			if (wall->GetVisible(index))
			{
				auto currentRectangle = dynamic_cast<C3DRectangle*>(visual->GetShape(index).get());

				auto amountVertex = currentRectangle->GetVertexes().size();
				auto amountIndexes = currentRectangle->GetIndexes().size();


				countVertex += amountVertex;
				countIndexes += amountIndexes;
			}
		}

	}

	m_vertices.reserve(countVertex);
	m_indicies.reserve(countIndexes);
	indexCount = 0;
	for (const auto & wall : walls)
	{
		auto visual = wall->GetVisual();
		for (size_t index = 0; index < visual->GetAmountShapes(); ++index)
		{
			if (wall->GetVisible(index))
			{

				auto currentRectangle = dynamic_cast<C3DRectangle*>(visual->GetShape(index).get());

				auto vertexes = currentRectangle->GetVertexes();
				auto indexes = currentRectangle->GetIndexes();

				auto append = [indexCount](uint32_t source) {
					return source + indexCount * 4;
				};

				boost::transform(indexes, indexes.begin(), append);

				m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());
				m_indicies.insert(m_indicies.end(), indexes.begin(), indexes.end());

				++indexCount;
			}
		}

	}

	indexCount = 0;

	/*
		const int rowCount = 2;
	for (unsigned ci = 0; ci < m_vertices.size(); ++ci)// 0-1
	{
		if (ci % 2 == 0)
		{
			for (unsigned ri = 0; ri < rowCount; ++ri)//0-1
			{
				unsigned index = ci * rowCount + ri;
				m_indicies.push_back(index + rowCount);
				m_indicies.push_back(index);
			}
		}
		else
		{
			for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
			{
				unsigned index = ci * rowCount + ri;
				m_indicies.push_back(index);
				m_indicies.push_back(index + rowCount);
			}
		}
	}

	*/
}
