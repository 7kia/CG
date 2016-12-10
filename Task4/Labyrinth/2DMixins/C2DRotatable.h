#pragma once

class I2DRotatable
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void		SetRotation(float rotation) = 0;
	virtual float		GetRotation() const = 0;
};

class C2DRotatable
	: public I2DRotatable
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
};