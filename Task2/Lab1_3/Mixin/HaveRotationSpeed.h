#pragma once

class IHaveRotationSpeed
{
public:
	virtual ~IHaveRotationSpeed() = default;

	virtual void	SetRotationSpeed(float rotation) = 0;
	virtual float	GetRotationSpeed() const = 0;

	virtual void	SetCurrentRotationSpeed(float rotation) = 0;
	virtual float	GetCurrentRotationSpeed() const = 0;

	virtual void	ResetCurrentRotationSpeed() = 0;
};


class CHaveRotationSpeed
	: public IHaveRotationSpeed
{
public:
	CHaveRotationSpeed(float rotation);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void	SetRotationSpeed(float rotation) override;
	float	GetRotationSpeed() const override;

	void	SetCurrentRotationSpeed(float rotation) override;
	float	GetCurrentRotationSpeed() const override;

	void	ResetCurrentRotationSpeed() override;

	//////////////////////////////////////////////////////////////////////
	// Methods
protected:
	float	m_rotationSpeed = 0.f;
	float	m_currentRotation = 0.f;
};