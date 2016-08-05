#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class IHaveDirection
{
public:
	virtual ~IHaveDirection() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			SetDirection(const glm::vec3 &value) = 0;
	// TODO : \/ see need rewrite this method, might incorrect return type
	virtual	glm::vec4		GetDirection() const = 0;
};

class CHaveDirection : public IHaveDirection
{
public:
	CHaveDirection();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			SetDirection(const glm::vec3 &value);
	glm::vec4		GetDirection() const;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4		m_direction;
};