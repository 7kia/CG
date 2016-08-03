#include "stdafx.h"
#include "HaveSpecular.h"

CHaveSpecular::CHaveSpecular()
	: IHaveSpecular()
{
}

void CHaveSpecular::SetSpecular(const glm::vec4 & Specular)
{
	m_specular = Specular;
}

glm::vec4 CHaveSpecular::GetSpecular() const
{
	return m_specular;
}
