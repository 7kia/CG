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

	m_indicies.push_back(0);
	m_indicies.push_back(1);
	m_indicies.push_back(3);

	m_indicies.push_back(1);
	m_indicies.push_back(2);
	m_indicies.push_back(3);
}
