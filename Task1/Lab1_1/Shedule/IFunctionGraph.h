#pragma once

#include "../Shape/CShape.h"

class IFunctionGraph// was exported from third lab by OOP
	: public CShape
{
public:
	virtual ~IFunctionGraph() = default;;

public:
	virtual void		SetStart(float start) = 0;
	virtual float		GetStart() const = 0;

	virtual void		SetEnd(float end) = 0;
	virtual float		GetEnd() const = 0;

	// Methods
protected:
	virtual float		GetValueFunction(float x) const = 0;
};