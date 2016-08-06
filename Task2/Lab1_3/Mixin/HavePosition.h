#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class IHavePosition
{
public:
	virtual ~IHavePosition() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void			SetPosition(const glm::vec3 &value) = 0;
	// TODO : \/ see need rewrite this method, might incorrect return type
	virtual	glm::vec3		GetPosition() const = 0;
	virtual void			Move(const glm::vec3 &value) = 0;
};

class CHavePosition : public IHavePosition
{
public:
	CHavePosition();
	CHavePosition(const glm::vec3 &value);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			SetPosition(const glm::vec3 &value);
	glm::vec3		GetPosition() const;

	void			Move(const glm::vec3 &value);
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec4		m_position;
};