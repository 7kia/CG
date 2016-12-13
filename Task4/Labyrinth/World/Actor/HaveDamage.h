#pragma once

#include "Features.h"

class CHaveDamage
{
public:
	CHaveDamage();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void				SetDamage(int value);
	void				AddDamage(int value);

	int					GetDamage() const;
protected:
	CStaticFeature		m_damage;
};