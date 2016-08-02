#include "stdafx.h"
#include "Dodecahedron.h"
#include "../Decorators/TransformShapeDecorator.h"

CDodecahedron::CDodecahedron()
	: ÑCompositeShape()
{
	//              Y     Z   x
	std::array<glm::vec3, 6> points;
	points[0] = { 0.f, 1.192f, 0.736f };
	points[1] = { -0.577f, 0.0f, 1.512f };
	points[2] = { 0.577f, 0.0f, 1.512f };
	points[3] = { 0.934f, 0.934f, 0.934f };
	points[4] = { 0.0f, 1.512f, 0.577f };
	points[5] = { -0.934f, 0.934f, 0.934f };

	CreatePentagon(points);

	points[0] = { 0.f, -1.192f, 0.736f };
	points[1] = { -0.934f, -0.934f, 0.934f };
	points[2] = { 0.0f, -1.512f, 0.577f };
	points[3] = { 0.934f, -0.934f, 0.934f };
	points[4] = { 0.577f, 0.0f, 1.512f };
	points[5] = { -0.577f, 0.0f, 1.512f };

	CreatePentagon(points);
}

void CDodecahedron::Update(float deltaTime)
{
	(void)deltaTime;
}

void CDodecahedron::CreatePentagon(const std::array<glm::vec3, 6> & points)
{	
	auto pPentagon = std::make_unique<CPentagon>();	
	m_shapes.emplace_back(std::move(pPentagon));

	CPentagon* addShape = dynamic_cast<CPentagon*>(m_shapes.back().get());
	for (size_t index = 0; index < 6; ++index)
	{
		addShape->SetVertex(index, points[index]);
	}

}