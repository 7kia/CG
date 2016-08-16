#include "stdafx.h"
#include "PhongMaterial.h"

CPhongModelMaterial::CPhongModelMaterial()
	: CMaterialCharactiristics()
{
}

void CPhongModelMaterial::Setup() const
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}


void CPhongModelMaterial::SetEmission(const glm::vec4 & emission)
{
	m_emission = emission;
}

glm::vec4 CPhongModelMaterial::GetEmission() const
{
	return m_emission;
}


float CPhongModelMaterial::GetShininess() const
{
	return m_shininess;
}

void CPhongModelMaterial::SetShininess(float shininess)
{
	m_shininess = shininess;
}