#include "stdafx.h"
#include "FunctionSurface.h"
#include <algorithm>

namespace
{
const float DOT_SIZE = 5.f;

struct CSurfaceTesselator : SMeshDataP3NT2
{
	void Tesselate(const glm::vec2 &rangeU
					, const glm::vec2 &rangeV
					, float step
					, const Function3D &function)
	{
		MakeVertexAttributes(rangeU, rangeV, step, function);
	}

	void CalculateTriangleStripIndicies(unsigned columnCount, unsigned rowCount)
	{
		indicies.clear();
		indicies.reserve((columnCount - 1) * rowCount * 2);

		for (unsigned ci = 0; ci < columnCount - 1; ++ci)
		{
			if (ci % 2 == 0)
			{
				for (unsigned ri = 0; ri < rowCount; ++ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index + rowCount);
					indicies.push_back(index);
				}
			}
			else
			{
				for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index);
					indicies.push_back(index + rowCount);
				}
			}
		}
		indicies.shrink_to_fit();
	}


	void MakeVertexAttributes(const glm::vec2 &rangeU
							, const glm::vec2 &rangeV
							, float step
							, const Function3D &function)
	{
		vertices.clear();
		// TODO : WARNING in two low strings is two magic number for correct draw Mobius strip
		const unsigned columnCount = unsigned((rangeU.y - rangeU.x) / step);
		const unsigned rowCount = unsigned((rangeV.y - rangeV.x) / step);

		// вычисляем позиции вершин.
		// рисуем двухсторонние полигоны

		for (unsigned ci = 0; ci < columnCount; ++ci)
		{
			const float U = rangeU.x + step * float(ci);
			for (unsigned ri = 0; ri < rowCount; ++ri)
			{
				const float V = rangeV.x + step * float(ri);
				SVertexP3NT2 vertex;
				vertex.position = function(U, V);

				// Only shader
				vertex.texCoord = glm::vec2(U, V);

				glm::vec3 dir1 = function(U + step, V) - vertex.position;
				glm::vec3 dir2 = function(U, V + step) - vertex.position;
				vertex.normal = -glm::normalize(glm::cross(dir1, dir2));

				//vertex.texCoord = glm::vec2(U, V);
				vertices.push_back(vertex);
			}
		}
		vertices.shrink_to_fit();

		CalculateTriangleStripIndicies(columnCount, rowCount);
	}

};


}

CSolidFunctionSurface::CSolidFunctionSurface(const Function3D &xFunction)
    : CIdentity3DShape(MeshType::TriangleStrip)
	, m_function(xFunction)
{
}

void CSolidFunctionSurface::Tesselate(const glm::vec2 &rangeU
									, const glm::vec2 &rangeV
									, float step) 

{ 
	CSurfaceTesselator tesselator;
	tesselator.Tesselate(rangeU, rangeV, step, m_function);	
	m_mesh.Copy(tesselator);
}

