#pragma once

#include <glm/mat4x4.hpp>

class IHaveDiffuse
{
public:
	virtual ~IHaveDiffuse() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual	void		SetDiffuse(const glm::vec4 &diffuse) = 0;
	virtual glm::vec4	GetDiffuse() const = 0;
};

class CHaveDiffuse : public IHaveDiffuse
{
public:
	CHaveDiffuse();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void		SetDiffuse(const glm::vec4 &diffuse) override;
	glm::vec4	GetDiffuse() const override;

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	glm::vec4	m_diffuse;
};