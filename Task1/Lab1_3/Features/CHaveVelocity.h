#pragma once

#include "glm/vec2.hpp"

class IHaveVelocity
{
public:
	virtual ~IHaveVelocity() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual glm::vec2	GetVelocity() const { return glm::vec2(); };
	virtual void		SetVelocity(const glm::vec2 &value) { (void)value; };

	//virtual glm::vec2	GetAcceleration() const { return glm::vec2(); };
	//virtual void		SetAcceleration(const glm::vec2 &acceleration) {};
};

class CHaveVelocity
	: public IHaveVelocity
{
public:
	CHaveVelocity();
	virtual ~CHaveVelocity() = default;
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