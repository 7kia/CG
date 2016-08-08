#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
	: ÑCompositeShape()
	, CHaveReferenceVertex(4)
{

	m_shapes.emplace_back(std::make_unique<CTriangle>());
	m_shapes.emplace_back(std::make_unique<CTriangle>());
	UpdateReference();

	/*
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

	*/

	SetVertex(0u, SVertexP3NT2(glm::vec3(-1.f, 1.f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(-1.f, 1.f, 0.f)));
	SetVertex(1u, SVertexP3NT2(glm::vec3(1.f, 1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 1.f, 0.f)));
	SetVertex(2u, SVertexP3NT2(glm::vec3(1.f, -1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(1.f, -1.f, 0.f)));
	SetVertex(3u, SVertexP3NT2(glm::vec3(-1.f, -1.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, -1.f, 0.f)));
}


void CRectangle::Update(float deltaTime)
{
	(void)deltaTime;
}

void CRectangle::UpdateReference()
{
	// Firts triangle
	const size_t size = m_pVertex.size();
	m_pVertex.clear();
	m_pVertex.resize(size);

	CTriangle* pTriangle = dynamic_cast<CTriangle*>(m_shapes.front().get());

	AddReferenceVertex(0u, pTriangle->GetReferenceToVertex(0u));
	AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(1u));
	AddReferenceVertex(3u, pTriangle->GetReferenceToVertex(2u));

	pTriangle = dynamic_cast<CTriangle*>(m_shapes.back().get());

	AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(0u));//2
	AddReferenceVertex(2u, pTriangle->GetReferenceToVertex(1u));//1
	AddReferenceVertex(3u, pTriangle->GetReferenceToVertex(2u));//0

}
