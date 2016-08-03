//#include "../stdafx.h"
#include "stdafx.h"
#include "Tetrahedron.h"

using namespace TetrahedronSpace;

CTetrahedron::CTetrahedron()
	: СCompositeShape()
{
	for (const STriangleFace &face : TETRAHEDRON_FACES)
	{
		auto triangle = std::make_unique<CTriangle>();

		triangle->SetVertex(0u, TETRAHEDRON_VERTICES[face.vertexIndex1]);
		triangle->SetVertex(1u, TETRAHEDRON_VERTICES[face.vertexIndex2]);
		triangle->SetVertex(2u, TETRAHEDRON_VERTICES[face.vertexIndex3]);

		m_shapes.emplace_back(std::move(triangle));
	}
}

void CTetrahedron::Update(float deltaTime)
{
	(void)deltaTime;
}