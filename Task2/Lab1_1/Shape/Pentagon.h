#pragma once

#include "CompositeShape.h"
#include "../Mixin/HaveVertex.h"
#include "Triangle.h"

namespace PentagonSpace
{
	const float HEIGHT_TRIANGLE = 0.80901f;
	const float SIDE = 1.1755164f;
}

class CPentagon final
	: public ÑCompositeShape
	, public CHaveReferenceVertex
{
public:
	CPentagon();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CHaveReferenceVertex
	void					SetVertex(int index, const Vertex & value) override;
	void					UpdateReference() override final;

	//--------------------------------------------
	// CShape
	void					Update(float deltaTime) override final;
	//--------------------------------------------
};
