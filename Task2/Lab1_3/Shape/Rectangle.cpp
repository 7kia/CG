#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
	: ÑCompositeShape()
{
	const glm::vec3 normal = { 0.f, 0.f, 1.f };

	{
		auto FirstTriangle = std::make_unique<CTriangle>();

		FirstTriangle->SetVertex(0u, SVertexP3NT2(glm::vec3(-1.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 1.f, 0.f)) );
		FirstTriangle->SetVertex(1u, SVertexP3NT2(glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 1.f, 0.f)) );
		FirstTriangle->SetVertex(2u, SVertexP3NT2(glm::vec3(-1.f, -1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, -1.f, 0.f)) );


		m_shapes.emplace_back(std::move(FirstTriangle));

	}
	{
		auto SecondTriangle = std::make_unique<CTriangle>();
		SecondTriangle->SetVertex(0u, SVertexP3NT2(glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 1.f, 0.f)));
		SecondTriangle->SetVertex(1u, SVertexP3NT2(glm::vec3(1.f, -1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(1.f, -1.f, 0.f)));
		SecondTriangle->SetVertex(2u, SVertexP3NT2(glm::vec3(-1.f, -1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, -1.f, 0.f)));

		m_shapes.emplace_back(std::move(SecondTriangle));
	}
}


void CRectangle::Update(float deltaTime)
{
	(void)deltaTime;
}