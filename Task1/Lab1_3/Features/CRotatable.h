#pragma once

class IRotatable
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void		SetRotation(float rotation) { (void)rotation;  };
	virtual float		GetRotation() const {};
};

class CRotatable
	: public IRotatable
{
//////////////////////////////////////////////////////////////////////
// Methods
public:

	float		GetRotation() const override;
	void		SetRotation(float rotation) override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	float		m_rotation = 0.f;
//////////////////////////////////////////////////////////////////////

};