//#include "../stdafx.h"
#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle()
	: CShape()
	, CHaveVertex(3u)
{
	const float shift = 0.66f;// origin int triangle center
	SetVertex(0u, glm::vec3(0.f, shift, 0.f));
	SetVertex(1u, glm::vec3(0.5f, -sqrtf(3.f) / 2.f + shift, 0.f));
	SetVertex(2u, glm::vec3(-0.5f, -sqrtf(3.f) / 2.f + shift, 0.f));
}


void CTriangle::Update(float deltaTime)
{
	(void)deltaTime;
}


void CTriangle::DrawOutputFaces() const
{
	// менее оптимальный способ рисования: прямая отправка данных
	// могла бы работать быстрее, чем множество вызовов glColor/glVertex.
	glBegin(GL_TRIANGLES);

	const Vertex &v1 = m_vertex[0];
	const Vertex &v2 = m_vertex[1];
	const Vertex &v3 = m_vertex[2];
	glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

	glColor4fv(glm::value_ptr(GetFaceColor()));
	glNormal3fv(glm::value_ptr(normal));
	glVertex3fv(glm::value_ptr(v1));
	glVertex3fv(glm::value_ptr(v2));
	glVertex3fv(glm::value_ptr(v3));
	
	glEnd();
}
