#pragma once

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "3DShape.h"

namespace SphereSpace
{
	const unsigned SPHERE_PRECISION = 40;

}


class CIdentity3DSphere final 
	: public C3DShape
{
public:
	CIdentity3DSphere(unsigned slices, unsigned stacks);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// C3DShape
	void Update(float) final {}
private:
	void Tesselate(unsigned slices, unsigned stacks);
	//--------------------------------------------
};