#include "stdafx.h"
#include "Dodecahedron.h"
#include "../Decorators/TransformShapeDecorator.h"

CDodecahedron::CDodecahedron()
	: ÑCompositeShape()
{
	{
		auto pPentagon = std::make_unique<CPentagon>();

		m_shapes.emplace_back(std::move(pPentagon));

		auto pPentagon2 = std::make_unique<CPentagon>();

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetChild(std::move(pPentagon2));


		const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), ToDegree(180.f), { 1.f, 0.f, 0.f });
		const glm::mat4 translateMatrix = glm::translate(glm::mat4(), { 0.f, 0.f, 0.f });

		const glm::mat4 resultTransformation = rotationMatrix * translateMatrix;

		pTransform->SetTransform(resultTransformation);

		m_shapes.emplace_back(std::move(pTransform));
	}
	{
		for (int index = 1; index <= 1; index++)
		{
			auto pPentagon = std::make_unique<CPentagon>();

			auto pTransform = std::make_unique<CTransformShapeDecorator>();
			pTransform->SetChild(std::move(pPentagon));


			const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), ToDegree(90.f * index), { 1.f, 0.f, 0.f });
			const glm::mat4 translateMatrix = glm::translate(glm::mat4(), { 0.f, PentagonSpace::HEIGHT_TRIANGLE, PentagonSpace::HEIGHT_TRIANGLE });

			const glm::mat4 resultTransformation = rotationMatrix * translateMatrix;

			pTransform->SetTransform(resultTransformation);

			m_shapes.emplace_back(std::move(pTransform));

			/*
			
			*/
		}


	}
}

void CDodecahedron::Update(float deltaTime)
{
	(void)deltaTime;
}
