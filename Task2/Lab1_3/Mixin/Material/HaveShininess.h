#pragma once

#include <glm/mat4x4.hpp>

class IHaveShininess
{
public:
	virtual ~IHaveShininess() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void	SetShininess(float GetShininess) = 0;
	virtual float	GetShininess() const = 0;
};

class CHaveShininess : public IHaveShininess
{
public:
	CHaveShininess();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void	SetShininess(float GetShininess) override;
	float	GetShininess() const override;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	float	m_shininess = 10.f;
};