#include "stdafx.h"
#include "3DRectangle.h"

C3DRectangle::C3DRectangle()
	: CIdentity3DShape()
{
	m_vertices.resize(4);

	SetVertex(0u, SVertexP3NT2(glm::vec3(-1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(-1.f, 1.f, 0.f)));
	SetVertex(1u, SVertexP3NT2(glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 1.f, 0.f)));
	SetVertex(2u, SVertexP3NT2(glm::vec3(1.f, -1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(1.f, -1.f, 0.f)));
	SetVertex(3u, SVertexP3NT2(glm::vec3(-1.f, -1.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, -1.f, 0.f)));

	m_indicies = { 0, 1, 3, 1, 2, 3};

}

void C3DRectangle::UpdateNormals()
{
	const Vertex &v1 = m_vertices[0].position;
	const Vertex &v2 = m_vertices[1].position;
	const Vertex &v3 = m_vertices[2].position;

	const Vertex &v4 = m_vertices[3].position;

	glm::vec3 normalFirstTriangle = glm::normalize(glm::cross(v2 - v1, v3 - v1));
	//glm::vec3 normalSecondTriangle = glm::normalize(glm::cross(v2 - v4, v3 - v4));

	if (abs(normalFirstTriangle.z) == 1)
	{
		normalFirstTriangle *= -1.f;
	}

	for (auto & vertex : m_vertices)
	{
		vertex.normal = normalFirstTriangle;
	}
	//m_vertices[0].normal = normalFirstTriangle;
	//m_vertices[3].normal = normalSecondTriangle;

}