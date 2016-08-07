#pragma once

class IHaveLinearVelocity
{
public:
	virtual ~IHaveLinearVelocity() = default;

	virtual void	SetLinearVelocity(float velocity) = 0;
	virtual float	GetLinearVelocity() const = 0;

	virtual void	SetCurrentLinearVelocity(float velocity) = 0;
	virtual float	GetCurrentLinearVelocity() const = 0;

	virtual void	ResetCurrentLinearVelocity() = 0;
};


class CHaveLinearVelocity
	: public IHaveLinearVelocity
{
public:
	CHaveLinearVelocity(float velocity);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void	SetLinearVelocity(float velocity) override;
	float	GetLinearVelocity() const override;

	void	SetCurrentLinearVelocity(float velocity) override;
	float	GetCurrentLinearVelocity() const override;

	void	ResetCurrentLinearVelocity() override;

//////////////////////////////////////////////////////////////////////
// Methods
protected:
	float	m_linearVelocity = 0.f;
	float	m_currentVelocity = 0.f;
};