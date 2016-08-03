#pragma once

#include <glm/mat4x4.hpp>

class IHaveSpecular
{
public:
	virtual ~IHaveSpecular() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual	void		SetSpecular(const glm::vec4 &Specular) = 0;
	virtual glm::vec4	GetSpecular() const = 0;
};

class CHaveSpecular : public IHaveSpecular
{
public:
	CHaveSpecular();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void		SetSpecular(const glm::vec4 &Specular) override;
	glm::vec4	GetSpecular() const override;

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	glm::vec4	m_specular;
};