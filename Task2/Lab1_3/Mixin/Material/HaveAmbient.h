#pragma once

#include <glm/mat4x4.hpp>

class IHaveAmbient
{
public:
	virtual ~IHaveAmbient() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual	void		SetAmbient(const glm::vec4 &ambient) = 0;
	virtual glm::vec4	GetAmbient() const = 0;
};

class CHaveAmbient : public IHaveAmbient
{
public:
	CHaveAmbient();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		SetAmbient(const glm::vec4 &ambient) override;
	glm::vec4	GetAmbient() const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4	m_ambient;
};