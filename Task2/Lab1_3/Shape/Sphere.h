#pragma once

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shape.h"

namespace SphereSpace
{
	const unsigned SPHERE_PRECISION = 40;

}


class CIdentitySphere final : public CShape
{
public:
	CIdentitySphere(unsigned slices, unsigned stacks);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// CShape
	void Update(float) final {}
	void Draw()const final;	
private:
	void Tesselate(unsigned slices, unsigned stacks) override final;
	//--------------------------------------------
};