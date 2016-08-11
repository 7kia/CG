#include "stdafx.h"
#include "3DRectangle.h"

C3DRectangle::C3DRectangle()
	: ÑComposite3DShape()
	, CHaveReferenceVertex(4)
{

	m_shapes.emplace_back(std::make_unique<C3DTriangle>());
	m_shapes.emplace_back(std::make_unique<C3DTriangle>());
	UpdateReference();

	/*
		{
		auto FirstTriangle = std::make_unique<C3DTriangle>();

		FirstTriangle->SetVertex(0u, SVertexP3NT2(glm::vec3(-1.f, 1.f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 1.f, 0.f)) );
		FirstTriangle->SetVertex(1u, SVertexP3NT2(glm::vec3(1.f, 1.f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 1.f, 0.f)) );
		FirstTriangle->SetVertex(2u, SVertexP3NT2(glm::vec3(-1.f, -1.f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, -1.f, 0.f)) );


		m_shapes.emplace_back(std::move(FirstTriangle));

	}
	{
		auto SecondTriangle = std::make_unique<C3DTriangle>();
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


void C3DRectangle::Update(float deltaTime)
{
	(void)deltaTime;
}

void C3DRectangle::UpdateReference()
{
	// Firts triangle
	const size_t size = m_pVertex.size();
	m_pVertex.clear();
	m_pVertex.resize(size);

	C3DTriangle* pTriangle = dynamic_cast<C3DTriangle*>(m_shapes.front().get());

	AddReferenceVertex(0u, pTriangle->GetReferenceToVertex(0u));
	AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(1u));
	AddReferenceVertex(3u, pTriangle->GetReferenceToVertex(2u));

	pTriangle = dynamic_cast<C3DTriangle*>(m_shapes.back().get());

	AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(0u));//2
	AddReferenceVertex(2u, pTriangle->GetReferenceToVertex(1u));//1
	AddReferenceVertex(3u, pTriangle->GetReferenceToVertex(2u));//0

}
