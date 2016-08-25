#pragma once

#include <glm/mat4x4.hpp>

class ITransformable
{
public:
	virtual ~ITransformable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void		SetTransform(const glm::mat4 &transform) = 0;
	virtual glm::mat4	GetTransform() const = 0;
};

class CTransformable : public ITransformable
{
public:
	CTransformable();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void		SetTransform(const glm::mat4 &transform) override;
	glm::mat4	GetTransform() const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::mat4	m_transform;
};