#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
	: ICircle()
{
}

CCircle::CCircle(float radius)
	: m_radius(radius)
{
}

void CCircle::SetRadius(float radius)
{
	m_radius = radius;
}

float CCircle::GetRadius() const
{
	return m_radius;
}

