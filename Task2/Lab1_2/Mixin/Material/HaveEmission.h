#pragma once

#include <glm/mat4x4.hpp>

class IHaveEmission
{
public:
	virtual ~IHaveEmission() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual	void		SetEmission(const glm::vec4 &emission) = 0;
	virtual glm::vec4	GetEmission() const = 0;
};

class CHaveEmission : public IHaveEmission
{
public:
	CHaveEmission();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void		SetEmission(const glm::vec4 &emission) override;
	glm::vec4	GetEmission() const override;

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	glm::vec4	m_emission;
};