#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

class IHave3DPosition
{
public:
	virtual ~IHave3DPosition() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			SetPosition(const glm::vec3 &value) = 0;
	virtual	glm::vec3		GetPosition() const = 0;
	virtual void			Move(const glm::vec3 &value) = 0;
};

class CHave3DPosition : public IHave3DPosition
{
public:
	CHave3DPosition();
	CHave3DPosition(const glm::vec3 &value);
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