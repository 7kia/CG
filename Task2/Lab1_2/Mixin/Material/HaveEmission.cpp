#include "stdafx.h"
#include "HaveEmission.h"

CHaveEmission::CHaveEmission()
	: IHaveEmission()
{
}

void CHaveEmission::SetEmission(const glm::vec4 & emission)
{
	m_emission = emission;
}

glm::vec4 CHaveEmission::GetEmission() const
{
	return m_emission;
}
