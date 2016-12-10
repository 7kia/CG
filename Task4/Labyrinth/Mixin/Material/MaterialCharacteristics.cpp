#include "stdafx.h"
#include "MaterialCharacteristics.h"


CMaterialCharactiristics::CMaterialCharactiristics()
{
}

void CMaterialCharactiristics::SetDiffuse(const glm::vec4 & diffuse)
{
	m_diffuse = diffuse;
}

glm::vec4 CMaterialCharactiristics::GetDiffuse() const
{
	return m_diffuse;
}


void CMaterialCharactiristics::SetAmbient(const glm::vec4 & ambient)
{
	m_ambient = ambient;
}

glm::vec4 CMaterialCharactiristics::GetAmbient() const
{
	return m_ambient;
}


void CMaterialCharactiristics::SetSpecular(const glm::vec4 & Specular)
{
	m_specular = Specular;
}

glm::vec4 CMaterialCharactiristics::GetSpecular() const
{
	return m_specular;
}