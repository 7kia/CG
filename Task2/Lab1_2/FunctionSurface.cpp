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
void CalculateNormals(std::vector<SVertexP3N> &vertices
					, const Function2D &xFunction
					, const Function2D &yFunction
					, const Function2D &zFunction
					, float step)
{
    for (SVertexP3N &v : vertices)
    {
        const glm::vec3 &position = v.position;
        glm::vec3 dir1 = glm::vec3(position.y, position.x, position.z + step) - position;
        glm::vec3 dir2 = glm::vec3(position.y, position.x + step, position.z) - position;
        v.normal = glm::normalize(glm::cross(dir1, dir2));
    }
}

/// Привязывает вершины к состоянию OpenGL,
/// затем вызывает 'callback'.
template <class T>
void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
{
    // Включаем режим vertex array и normal array.
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    // Выполняем привязку vertex array и normal array
    const size_t stride = sizeof(SVertexP3N);
    glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
    glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));

    // Выполняем внешнюю функцию.
    callback();

    // Выключаем режим vertex array и normal array.
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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
    const unsigned columnCount = unsigned((rangeU.y - rangeU.x) / step);
    const unsigned rowCount = unsigned((rangeV.y - rangeV.x) / step);

    // вычисляем позиции вершин.
    for (unsigned ci = 0; ci < columnCount; ++ci)
    {
        const float U = rangeU.x + step * float(ci);
        for (unsigned ri = 0; ri < rowCount; ++ri)
        {
            const float V = rangeV.x + step * float(ri);
			m_vertices.push_back(SVertexP3N( glm::vec3(m_xFunction(U, V), m_yFunction(U, V), m_zFunction(U, V))));
        }
    }
    CalculateNormals(m_vertices
					, m_xFunction
					, m_yFunction
					, m_zFunction
					, step);
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
    DoWithBindedArrays(m_vertices, [this] {
        glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
                       GL_UNSIGNED_INT, m_indicies.data());
    });
}

