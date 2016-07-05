#pragma once

#include "../Shape/StaticShape.h"
#include "../Features/CHaveVelocity.h"
// For one constant not need
//namespace
//{
	const glm::vec2 GRAVITY = { 0.f, -10.f };
//}

class CDynamicBody 
	: public CHaveVelocity
	, public CStaticShape
{
public:
	CDynamicBody();
	virtual ~CDynamicBody() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// @param dt - ������� �� ������� � ���������� ������� Advance.
	// @param acceleration - ���������, ����������� �� �������.
	void		Advance(float dt) override;

	void		ApplyAcceleration(const glm::vec2 & acceleration);
};
