#pragma once

#include <glm/mat4x4.hpp>

class CMaterialCharactiristics
{
public:
	CMaterialCharactiristics();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		SetDiffuse(const glm::vec4 &diffuse);
	glm::vec4	GetDiffuse() const;

	void		SetAmbient(const glm::vec4 &ambient);
	glm::vec4	GetAmbient() const;

	void		SetSpecular(const glm::vec4 &Specular);
	glm::vec4	GetSpecular() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4	m_diffuse;
	glm::vec4	m_ambient;
	glm::vec4	m_specular;
};