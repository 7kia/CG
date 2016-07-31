#pragma once

#include "Shape.h"
#include "CompositeShape.h"
#include "Triangle.h"

namespace TetrahedronSpace
{

	// Сторона тетраэдра равна √3,
	// расстояние от центра грани до вершины равно 1.
	const Vertex TETRAHEDRON_VERTICES[] = {
		{ 0.f, 0.f, -1.0f },
		{ 0.f, 0.f , 0.f },//{ 0.f, 0.f , 0.f },
		{ 0.5f, -sqrtf(3.f) / 2.f, 0.f },//{ 0.5f, -sqrtf(3.f) / 2.f, 0.f },
		{ -0.5f, -sqrtf(3.f) / 2.f, 0.f },//{ -0.5f, -sqrtf(3.f) / 2.f, 0.f }
	};


	const STriangleFace TETRAHEDRON_FACES[] = {
		{ 0, 1, 2, 0 },
		{ 0, 3, 1, 0 },
		{ 2, 1, 3, 0 },
		{ 0, 2, 3, 0 },
	};

}

class CTetrahedron final 
	: public СCompositeShape
{
public:
	CTetrahedron();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// СCompositeShape
	void Update(float deltaTime) override final;
};