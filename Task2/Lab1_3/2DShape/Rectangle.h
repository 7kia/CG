#pragma once

#include "2DShape.h"
#include "Static2DShape.h"

struct SSize
{
	SSize();
	SSize(float width, float height);
	float width = 0.f;
	float height = 0.f;
};

class IRectangle
{
public:
	virtual ~IRectangle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void				SetWidth(float width) = 0;
	virtual float				GetWidth() const = 0;

	virtual void				SetHeight(float height) = 0;
	virtual float				GetHeight() const = 0;
};


class CRectangle
	: public IRectangle
{
public:
	CRectangle();
	CRectangle(SSize size);
	CRectangle(float width, float height);

	virtual ~CRectangle() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void				SetWidth(float width);
	float				GetWidth() const;

	void				SetHeight(float height);
	float				GetHeight() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	float				m_width = NONE_VALUE::FLOAT;
	float				m_height = NONE_VALUE::FLOAT;
//////////////////////////////////////////////////////////////////////


};

