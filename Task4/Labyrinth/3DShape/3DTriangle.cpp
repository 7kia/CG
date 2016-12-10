#include "stdafx.h"
#include "3DTriangle.h"

C3DTriangle::C3DTriangle()
	: CIdentity3DShape()
{
	m_vertices.resize(3);
	m_indicies.resize(3);

	const float shift = 0.66f;// origin int triangle center
	const auto firstPosition = glm::vec3(0.f, shift, 0.f);
	const auto secondPosition = glm::vec3(0.5f, -sqrtf(3.f) / 2.f + shift, 0.f);
	const auto thirdPosition = glm::vec3(-0.5f, -sqrtf(3.f) / 2.f + shift, 0.f);

	SetVertex(0u, SVertexP3NT2(firstPosition, glm::vec2(0.f, 0.f), firstPosition) );
	SetVertex(1u, SVertexP3NT2(secondPosition, glm::vec2(1.f, 0.f), secondPosition) );
	SetVertex(2u, SVertexP3NT2(thirdPosition, glm::vec2(1.f, 1.f), thirdPosition));

	m_indicies = { 0, 1, 2 };
}

