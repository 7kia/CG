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
	m_radius = Convert::ToBox(radius);
}

float CCircle::GetRadius() const
{
	return Convert::ToNormal(m_radius);
}

