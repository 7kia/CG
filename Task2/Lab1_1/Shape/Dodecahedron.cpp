#include "stdafx.h"
#include "Dodecahedron.h"
#include "../Decorators/TransformShapeDecorator.h"

CDodecahedron::CDodecahedron()
	: ÑCompositeShape()
{
	//              Y     Z   x
	std::array<glm::vec3, 6> points;
	points[0] = { 0.f, 0.676f, 1.094f };
	points[1] = { -0.577f, 0.0f, 1.512f };
	points[2] = { 0.577f, 0.0f, 1.512f };
	points[3] = { 0.934f, 0.934f, 0.934f };
	points[4] = { 0.0f, 1.512f, 0.577f };
	points[5] = { -0.934f, 0.934f, 0.934f };

	CreatePentagon(points);

	points[0] = { 0.f, -0.676f, 1.094f };
	points[1] = { -0.934f, -0.934f, 0.934f };
	points[2] = { 0.0f, -1.512f, 0.577f };
	points[3] = { 0.934f, -0.934f, 0.934f };
	points[4] = { 0.577f, 0.0f, 1.512f };
	points[5] = { -0.577f, 0.0f, 1.512f };

	CreatePentagon(points);
	//              Y     Z   x
	points[0] = { 1.094f, 0.f, 0.676f };
	points[1] = { 0.934f, -0.934f, 0.934f };//1
	points[2] = { 1.512f, -0.577f, 0.0f };//2
	points[3] = { 1.512f, 0.577f, 0.0f };//3
	points[4] = { 0.934f, 0.934f, 0.934f };//4
	points[5] = { 0.577f, 0.f, 1.512f };//5

	CreatePentagon(points);

	points[0] = { -1.094f, 0.f, 0.676f };
	points[1] = { -1.512f, -0.577f, 0.0f };//2
	points[2] = { -0.934f, -0.934f, 0.934f };//1
	points[3] = { -0.577f, 0.f, 1.512f };//5
	points[4] = { -0.934f, 0.934f, 0.934f };//4
	points[5] = { -1.512f, 0.577f, 0.0f };//3

	CreatePentagon(points);
	///////////////////////////////////////
	//              Y     Z   x
	points[0] = { 0.f, 0.676f, -1.094f };
	points[1] = { -0.934f, 0.934f, -0.934f };
	points[2] = { 0.0f, 1.512f, -0.577f };
	points[3] = { 0.934f, 0.934f, -0.934f };
	points[4] = { 0.577f, 0.0f, -1.512f };
	points[5] = { -0.577f, 0.0f, -1.512f };

	CreatePentagon(points);

	points[0] = { 0.f, -0.676f, -1.094f };
	points[1] = { -0.577f, 0.0f, -1.512f };
	points[2] = { 0.577f, 0.0f, -1.512f };
	points[3] = { 0.934f, -0.934f, -0.934f };
	points[4] = { 0.0f, -1.512f, -0.577f };
	points[5] = { -0.934f, -0.934f, -0.934f };

	CreatePentagon(points);
	//              Y     Z   x
	points[0] = { 1.094f, 0.f, -0.676f };
	points[1] = { 0.577f, 0.f, -1.512f };//5
	points[2] = { 0.934f, 0.934f,- 0.934f };//4
	points[3] = { 1.512f, 0.577f, -0.0f };//3
	points[4] = { 1.512f, -0.577f, -0.0f };//2
	points[5] = { 0.934f, -0.934f, -0.934f };//1

	CreatePentagon(points);

	points[0] = { -1.094f, 0.f, -0.676f };
	points[1] = { -1.512f, 0.577f, -0.0f };//3
	points[2] = { -0.934f, 0.934f, -0.934f };//4
	points[3] = { -0.577f, 0.f, -1.512f };//5
	points[4] = { -0.934f, -0.934f, -0.934f };//1
	points[5] = { -1.512f, -0.577f, -0.0f };//2

	CreatePentagon(points);
	/////////////////////////
	points[0] = { -1.094f, 0.f, -0.676f };
	points[1] = { -1.512f, 0.577f, -0.0f };//3
	points[2] = { -0.934f, 0.934f, -0.934f };//4
	points[3] = { -0.577f, 0.f, -1.512f };//5
	points[4] = { -0.934f, -0.934f, -0.934f };//1
	points[5] = { -1.512f, -0.577f, -0.0f };//2

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