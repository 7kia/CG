#include "stdafx.h"
#include "FunctionSurface.h"
#include <algorithm>

namespace
{
const float DOT_SIZE = 5.f;


// вычисляет нормали численным методом,
// с помощью векторного произведения.
void CalculateNormals(std::vector<SVertexP3NT2> &vertices, float step)
{
	for(SVertexP3NT2 & v : vertices)
	{
        const glm::vec3 &position = v.position;
    }
	
}

void CalculateTriangleStripIndicies(std::vector<uint32_t> & indicies, unsigned columnCount, unsigned rowCount)
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

}

CSolidFunctionSurface::CSolidFunctionSurface(const Function3D &xFunction)
    : m_function(xFunction)
{
}

void CSolidFunctionSurface::Tesselate(const glm::vec2 &rangeU
									, const glm::vec2 &rangeV
									, float step) 

{
    m_vertices.clear();
	// TODO : WARNING in two low strings is two magic number for correct draw Mobius strip
    const unsigned columnCount = unsigned((rangeU.y - rangeU.x) / step) + 2;
    const unsigned rowCount = unsigned((rangeV.y - rangeV.x) / step) + 1;

    // вычисляем позиции вершин.
	// рисуем двухсторонние полигоны
	
	// TODO : WARNING in two low strings is two magic number for correct draw Klein bottle
	const float maxU = rangeU.x + step * float(columnCount - 1 - 2);
	const float maxV = rangeV.x + step * float(rowCount - 1 - 1);

	for (unsigned ci = 0; ci < columnCount; ++ci)
	{
		const float U = rangeU.x + step * float(ci);
		for (unsigned ri = 0; ri <= rowCount; ++ri)
		{
			const float V = rangeV.x + step * float(ri);
			SVertexP3NT2 vertex;
			vertex.position = m_function(U, V);

			// Only shader
			vertex.texCoord = glm::vec2(U, V);

			glm::vec3 dir1 = m_function(U + step, V) - vertex.position;
			glm::vec3 dir2 = m_function(U, V + step) - vertex.position;
			vertex.normal = -glm::normalize(glm::cross(dir1, dir2));

			//vertex.texCoord = glm::vec2(U, V);
			m_vertices.push_back(vertex);
		}
	}


    // вычисляем индексы вершин.
	CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
	m_vertices.shrink_to_fit();
}

void CSolidFunctionSurface::Draw() const
{
	// Рисуем обе стороны
	glFrontFace(GL_CW);
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
	glFrontFace(GL_CCW);

    DoWithBindedArrays(m_vertices, [this] {
        glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
                       GL_UNSIGNED_INT, m_indicies.data());
    });
}

