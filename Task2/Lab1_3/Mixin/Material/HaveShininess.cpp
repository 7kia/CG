#include "stdafx.h"
#include "HaveShininess.h"

CHaveShininess::CHaveShininess()
	: IHaveShininess()
{
}

float CHaveShininess::GetShininess() const
{
	return m_shininess;
}

void CHaveShininess::SetShininess(float shininess)
{
	m_shininess = shininess;
}