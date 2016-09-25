#include "stdafx.h"
#include "FunctionSurface.h"
#include <algorithm>

namespace
{
const float DOT_SIZE = 5.f;

glm::vec3 GetPosition(const Function2D &fn, float x, float z)
{
    const float y = fn(x, z);
    return {x, y, z};
}

// вычисляет нормали численным методом,
// с помощью векторного произведения.
void CalculateNormals(std::vector<SVertexP3NT2> &vertices, float step)
{
	for(SVertexP3NT2 & v : vertices)
	{
        const glm::vec3 &position = v.position;
        glm::vec3 dir1 = glm::vec3(position.y, position.x, position.z + step) - position;
        glm::vec3 dir2 = glm::vec3(position.y, position.x + step, position.z) - position;
		v.normal = glm::normalize(glm::cross(dir1, dir2));
    }
	
}


}

CSolidFunctionSurface::CSolidFunctionSurface(const Function2D &xFunction
											, const Function2D &yFunction
											, const Function2D &zFunction)
    : m_xFunction(xFunction)
	, m_yFunction(yFunction)
	, m_zFunction(zFunction)
{
}

void CSolidFunctionSurface::Tesselate(const glm::vec2 &rangeU
									, const glm::vec2 &rangeV
									, float step) 

{
    m_vertices.clear();
    const unsigned columnCount = unsigned((rangeU.y - rangeU.x) / step) + 2;
    const unsigned rowCount = unsigned((rangeV.y - rangeV.x) / step) + 1;

    // вычисляем позиции вершин.
	// рисуем двухсторонние полигоны
	
		for (unsigned ci = 0; ci < columnCount; ++ci)
		{
			const float U = rangeU.x + step * float(ci);
			for (unsigned ri = 0; ri < rowCount; ++ri)
			{
				const float V = rangeV.x + step * float(ri);
				SVertexP3NT2 vertex;
				vertex.position = glm::vec3(glm::vec3(m_xFunction(U, V), m_yFunction(U, V), m_zFunction(U, V)));
				m_vertices.push_back(vertex);
			}
		}

    CalculateNormals(m_vertices, step);
    // вычисляем индексы вершин.
    for (unsigned ci = 0; ci < columnCount - 1; ++ci)
    {
        if (ci % 2 == 0)
        {
            for (unsigned ri = 0; ri < rowCount; ++ri)
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

