#include "stdafx.h"
#include "Labyrinth.h"
#include "Map.h"

CLabyrinth::CLabyrinth()
	: CIdentity3DShape()
{
}

void CLabyrinth::BuildLabyrinth(const std::vector<PWall> & walls)
{
	size_t indexCount = 0;
	for (const auto & wall : walls)
	{
		auto visual = wall->GetVisual();
		for (size_t index = 0; index < visual->GetAmountShapes(); ++index)
		{
			auto currentRectangle = dynamic_cast<C3DRectangle*>(visual->GetShape(index).get());
			
			
				auto vertexes = currentRectangle->GetVertexes();
				
				m_vertices.insert(m_vertices.end(), vertexes.begin(), vertexes.end());

				for (size_t count = 0; count < vertexes.size(); ++count)// TODO : see is it correct
				{
					m_indicies.push_back(indexCount++);
				}
				//m_indicies.insert(m_indicies.end(), indexes.begin(), indexes.end());
			
		}


	}



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
