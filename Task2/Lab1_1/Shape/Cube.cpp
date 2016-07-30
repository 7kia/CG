#include "stdafx.h"
#include "Cube.h"

using namespace CubeSpace;

CIdentityCube::CIdentityCube()
	: m_alpha(1)
{
	// Используем белый цвет по умолчанию.
	for (glm::vec3 &color : m_colors)
	{
		color.x = 1;
		color.y = 1;
		color.z = 1;
	}
}

void CIdentityCube::Update(float deltaTime)
{
	(void)deltaTime;
}

void CIdentityCube::Draw() const
{
	if (m_alpha < 0.99f)
	{
		glFrontFace(GL_CW);
		OutputFaces();
		glFrontFace(GL_CCW);
	}
	OutputFaces();
}

void CIdentityCube::SetFaceColor(CubeFace face, const glm::vec3 &color)
{
	const size_t index = static_cast<size_t>(face);
	assert(index < COLORS_COUNT);
	m_colors[index] = color;
}

void CIdentityCube::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void CIdentityCube::OutputFaces() const
{
	// менее оптимальный способ рисования: прямая отправка данных
	// могла бы работать быстрее, чем множество вызовов glColor/glVertex.
	glBegin(GL_TRIANGLES);

	for (const STriangleFace &face : CUBE_FACES)
	{
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
}