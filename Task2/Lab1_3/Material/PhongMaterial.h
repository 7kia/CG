#pragma once

#include "../Mixin/Material/MaterialCharacteristics.h"

class CPhongModelMaterial
	: public CMaterialCharactiristics
{
public:
	CPhongModelMaterial();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		Setup() const;


	void		SetEmission(const glm::vec4 &emission);
	glm::vec4	GetEmission() const;

	void		SetShininess(float GetShininess);
	float		GetShininess() const;
//////////////////////////////////////////////////////////////////////
// Data
private:
	glm::vec4	m_emission;
	float		m_shininess = 0.2f;

};
