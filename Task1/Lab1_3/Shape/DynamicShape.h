#pragma once

#include "../Shape/StaticShape.h"
#include "../Features/CHaveVelocity.h"
// For one constant not need
//namespace
//{
	const glm::vec2 GRAVITY = { 0.f, 0.f };
//}

class CDynamicBody 
	: public CHaveVelocity
	, public CStaticShape
{
public:
	virtual ~CDynamicBody() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - ������� �� ������� � ���������� ������� Advance.
	// @param acceleration - ���������, ����������� �� �������.
	void		Advance(float dt);

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
