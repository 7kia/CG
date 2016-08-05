#include "stdafx.h"
#include "HaveAmbient.h"

CHaveAmbient::CHaveAmbient()
	: IHaveAmbient()
{
}

void CHaveAmbient::SetAmbient(const glm::vec4 & ambient)
{
	m_ambient = ambient;
}

glm::vec4 CHaveAmbient::GetAmbient() const
{
	return m_ambient;
}
