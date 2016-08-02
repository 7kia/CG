#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
	: ÑCompositeShape()
{
	{
		auto FirstTriangle = std::make_unique<CTriangle>();
		FirstTriangle->SetVertex(0u, glm::vec3(-1.f, 1.f, 0.f));
		FirstTriangle->SetVertex(1u, glm::vec3(1.f, 1.f, 0.f));
		FirstTriangle->SetVertex(2u, glm::vec3(-1.f, -1.f, 0.f));


		m_shapes.emplace_back(std::move(FirstTriangle));

	}
	{
		auto SecondTriangle = std::make_unique<CTriangle>();
		SecondTriangle->SetVertex(0u, glm::vec3(1.f, 1.f, 0.f));
		SecondTriangle->SetVertex(1u, glm::vec3(1.f, -1.f, 0.f));
		SecondTriangle->SetVertex(2u, glm::vec3(-1.f, -1.f, 0.f));

		m_shapes.emplace_back(std::move(SecondTriangle));
	}
}


void CRectangle::Update(float deltaTime)
{
	(void)deltaTime;
}