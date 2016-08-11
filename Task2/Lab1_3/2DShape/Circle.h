#pragma once

#include "Static2DShape.h"
#include "Dynamic2DShape.h"

#include <vector>
#include <memory>


namespace DEFAULT_BALL
{
	const float	RADIUSE = 10.f;
	const float	THIKNESS = 1.f;
	const float	SPEED = 900.f;
}

class ICircle
{
public:
	virtual ~ICircle() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	virtual void		SetRadius(float radius) = 0;
	virtual float		GetRadius() const = 0;
	//////////////////////////////////////////////////////////////////////
};

class CCircle
	: public ICircle
{
public:
	CCircle();
	CCircle(float radius);

	virtual ~CCircle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		SetRadius(float radius) override;
	float		GetRadius() const override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	float		m_radius = DEFAULT_BALL::RADIUSE;
//////////////////////////////////////////////////////////////////////
};