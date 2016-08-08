//#include "../stdafx.h"
#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle()
	: CShape()
	, CHaveThreeVertex()
{
	const float shift = 0.66f;// origin int triangle center
	const glm::vec3 normal = { 0.f, 0.f, 1.f };
	SetVertex(0u, SVertexP3NT2(glm::vec3(0.f, shift, 0.f), glm::vec2(0.f, 0.f), normal) );
	SetVertex(1u, SVertexP3NT2(glm::vec3(0.5f, -sqrtf(3.f) / 2.f + shift, 0.f), glm::vec2(1.f, 0.f), normal) );
	SetVertex(2u, SVertexP3NT2(glm::vec3(-0.5f, -sqrtf(3.f) / 2.f + shift, 0.f), glm::vec2(1.f, 1.f), normal));
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

	const Vertex &v1 = m_vertex[0].position;
	const Vertex &v2 = m_vertex[1].position;
	const Vertex &v3 = m_vertex[2].position;
	// TODO : rewrite for computing normal
	glm::vec3 normal = m_vertex[0].normal;//glm::normalize(glm::cross(v2 - v1, v3 - v1));

	glNormal3fv(glm::value_ptr(normal));
	glVertex3fv(glm::value_ptr(v1));
	glVertex3fv(glm::value_ptr(v2));
	glVertex3fv(glm::value_ptr(v3));
	
	glEnd();
}
