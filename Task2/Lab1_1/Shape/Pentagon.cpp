#include "stdafx.h"
#include "Pentagon.h"
#include "../Decorators/TransformShapeDecorator.h"

CPentagon::CPentagon()
{
	{
		auto FirstTriangle = std::make_unique<CTriangle>();
		FirstTriangle->SetVertex(0u, glm::vec3(0.f, 0.f, 0.f));
		FirstTriangle->SetVertex(1u, glm::vec3(0.5877852f, -0.80901f, 0.f));
		FirstTriangle->SetVertex(2u, glm::vec3(-0.5877852f, -0.80901f, 0.f));

		m_shapes.emplace_back(std::move(FirstTriangle));
	}
	{
		for (int index = 1; index <= 4; index++)
		{
			auto triangle = std::make_unique<CTriangle>();
			*triangle = *dynamic_cast<CTriangle*>(m_shapes[0].get());

			auto pTransform = std::make_unique<CTransformShapeDecorator>();
			pTransform->SetChild(std::move(triangle));


			const glm::mat4 transformation = glm::rotate(glm::mat4(), ToDegree(72.f * index), { 0.f, 0.f, 1.f });

			pTransform->SetTransform(transformation);

			m_shapes.emplace_back(std::move(pTransform));
		}


	}
}

void CPentagon::Update(float deltaTime)
{
	(void)deltaTime;
}
