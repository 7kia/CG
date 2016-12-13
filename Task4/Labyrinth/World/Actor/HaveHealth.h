#pragma once

#include "Features.h"

class IHavehealth
{
public:
	virtual ~IHavehealth() = default;

	virtual void AddToMaxHealth(int value) = 0;
	virtual int	GetMaxHealth() const = 0;
};

class CHaveHealth : public IHavehealth
{
public:
	CHaveHealth();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void				SetHealth(int value);
	void				AddHealth(int value);

	void				SetMaxHealth(int value);
	void				AddToMaxHealth(int value) override;

	int					GetHealth() const;
	int					GetMaxHealth() const override;

protected:
	CDynamicFeature		m_health;
};