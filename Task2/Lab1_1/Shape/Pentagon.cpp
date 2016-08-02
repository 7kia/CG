#include "stdafx.h"
#include "Pentagon.h"
#include "../Decorators/TransformShapeDecorator.h"

using namespace PentagonSpace;

CPentagon::CPentagon()
	: СCompositeShape()
	, CHaveReferenceVertex(6)
{
	{
		auto FirstTriangle = std::make_unique<CTriangle>();

		const glm::vec3 startPoint = glm::vec3(0.f, 0.f, 0.f);
		const glm::vec3 secondPoint = glm::vec3(SIDE / 2.f, -HEIGHT_TRIANGLE, 0.f);
		const glm::vec3 thirdPoint = glm::vec3(-SIDE / 2.f, -HEIGHT_TRIANGLE, 0.f);

		FirstTriangle->SetVertex(0u, startPoint);
		FirstTriangle->SetVertex(1u, secondPoint);
		FirstTriangle->SetVertex(2u, thirdPoint);

		m_shapes.emplace_back(std::move(FirstTriangle));

		// other
		for (int index = 1; index <= 4; index++)
		{
			auto triangle = std::make_unique<CTriangle>();
			*triangle = *dynamic_cast<CTriangle*>(m_shapes[0].get());

			//поворот вершин треугольника
			glm::mat4 secondPosition;
			secondPosition[0][3] = secondPoint.x;
			secondPosition[1][3] = secondPoint.y;
			secondPosition[2][3] = secondPoint.z;
			secondPosition = glm::rotate(secondPosition, ToDegree(72.f * index), { 0.f, 0.f, 1.f });

			glm::mat4 thirdPosition;
			thirdPosition[0][3] = thirdPoint.x;
			thirdPosition[1][3] = thirdPoint.y;
			thirdPosition[2][3] = thirdPoint.z;
			thirdPosition = glm::rotate(thirdPosition, ToDegree(72.f * index), { 0.f, 0.f, 1.f });

			// запись позиции
			triangle->SetVertex(1u, glm::vec3(secondPosition[0][3], secondPosition[1][3], secondPosition[2][3]));
			triangle->SetVertex(2u, glm::vec3(thirdPosition[0][3], thirdPosition[1][3], thirdPosition[2][3]));
			m_shapes.emplace_back(std::move(triangle));

		}


	}
	UpdateReference();
}

void CPentagon::SetVertex(int index, const Vertex & value)
{
	CHaveReferenceVertex::CheckIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
}

void CPentagon::Update(float deltaTime)
{
	(void)deltaTime;
}

void CPentagon::UpdateReference()
{
	// Firts triangle
	const size_t size = m_pVertex.size();
	m_pVertex.clear();
	m_pVertex.resize(size);

	CTriangle* pTriangle = dynamic_cast<CTriangle*>(m_shapes.front().get());

	AddReferenceVertex(0u, pTriangle->GetReferenceToVertex(0u));
	AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(1u));
	AddReferenceVertex(2u, pTriangle->GetReferenceToVertex(2u));

	// other
	for (int index = 1; index <= 4; index++)
	{
		pTriangle = dynamic_cast<CTriangle*>(m_shapes[index].get());

		AddReferenceVertex(0u, pTriangle->GetReferenceToVertex(0u));
		AddReferenceVertex(index + 1, pTriangle->GetReferenceToVertex(1u));
		if ((index + 2) <= 5)
		{
			AddReferenceVertex(index + 2, pTriangle->GetReferenceToVertex(2u));
		}
		else
		{
			AddReferenceVertex(1u, pTriangle->GetReferenceToVertex(2u));
		}
	}
}
