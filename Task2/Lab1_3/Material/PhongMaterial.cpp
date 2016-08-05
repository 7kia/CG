#include "stdafx.h"
#include "PhongMaterial.h"

CPhongModelMaterial::CPhongModelMaterial()
	: CHaveEmission()
	, CHaveAmbient()
	, CHaveDiffuse()
	, CHaveSpecular()
	, CHaveShininess()
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