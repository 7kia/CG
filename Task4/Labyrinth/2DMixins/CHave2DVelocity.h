#pragma once

#include "glm/vec2.hpp"

class IHave2DVelocity
{
public:
	virtual ~IHave2DVelocity() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual glm::vec2	GetVelocity() const = 0;
	virtual void		SetVelocity(const glm::vec2 &value) = 0;

	//virtual glm::vec2	GetAcceleration() const = 0;
	//virtual void		SetAcceleration(const glm::vec2 &acceleration) = 0;
};

class CHave2DVelocity
	: public IHave2DVelocity
{
public:
	CHave2DVelocity();
	virtual ~CHave2DVelocity() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	glm::vec2	GetVelocity() const override;
	void		SetVelocity(const glm::vec2 &GetVelocity) override;

	//glm::vec2	GetAcceleration() const override;
	//void		SetAcceleration(const glm::vec2 &acceleration) override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::vec2	m_velocity;
	glm::vec2	m_acceleration;
//////////////////////////////////////////////////////////////////////
};