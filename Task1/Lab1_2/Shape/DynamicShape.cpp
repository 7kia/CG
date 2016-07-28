#include "stdafx.h"
#include "DynamicShape.h"

CDynamicBody::CDynamicBody()
	: IHaveVelocity()
	, CStaticShape()
{

	SetVelocity(NONE_VALUE::GLM_VEC2);
}

void CDynamicBody::Advance(float dt)
{
	(void)dt;
}


void CDynamicBody::ApplyAcceleration(const glm::vec2 & acceleration)
{
	SetAcceleration(GetAcceleration() + acceleration);
}

void CDynamicBody::CheckParametres()
{
	if (GetVelocity() == NONE_VALUE::GLM_VEC2)
	{
		throw std::runtime_error("Not define velocity!!!");
	}
}
