//#include "../stdafx.h"
#include "stdafx.h"
#include "3DTriangle.h"

C3DTriangle::C3DTriangle()
	: C3DShape()
{
	const float shift = 0.66f;// origin int triangle center
	const auto firstPosition = glm::vec3(0.f, shift, 0.f);
	const auto secondPosition = glm::vec3(0.5f, -sqrtf(3.f) / 2.f + shift, 0.f);
	const auto thirdPosition = glm::vec3(-0.5f, -sqrtf(3.f) / 2.f + shift, 0.f);

	SetVertex(0u, SVertexP3NT2(firstPosition, glm::vec2(0.f, 0.f), firstPosition) );
	SetVertex(1u, SVertexP3NT2(secondPosition, glm::vec2(1.f, 0.f), secondPosition) );
	SetVertex(2u, SVertexP3NT2(thirdPosition, glm::vec2(1.f, 1.f), thirdPosition));

	m_indicies.push_back(0);
	m_indicies.push_back(1);
	m_indicies.push_back(2);

}


void C3DTriangle::Update(float deltaTime)
{
	(void)deltaTime;
}


void C3DTriangle::DrawOutputFaces() const
{
	// менее оптимальный способ рисования: прямая отправка данных
	// могла бы работать быстрее, чем множество вызовов glColor/glVertex.
	glBegin(GL_TRIANGLES);

	const Vertex &v1 = m_vertices[0].position;
	const Vertex &v2 = m_vertices[1].position;
	const Vertex &v3 = m_vertices[2].position;
	// TODO : rewrite for computing normal
	glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

	glNormal3fv(glm::value_ptr(normal));
	glVertex3fv(glm::value_ptr(v1));
	glVertex3fv(glm::value_ptr(v2));
	glVertex3fv(glm::value_ptr(v3));
	
	glEnd();
}
