#pragma once

#include "HaveFaceColor.h"
#include "../Shape/IShape.h"

class CTransparentShape
	: public CHaveFaceColor
	, public IShape
{
public:
	CTransparentShape();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	void			Draw() const override final;
protected:
	virtual void	DrawOutputFaces() const = 0;
};