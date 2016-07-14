#pragma once

#include "CDrawable.h"

class IShape
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual ~IShape() = default;

	virtual void			SetOutlineColor(const glm::vec3 &color) = 0;
	virtual glm::vec3		GetOutlineColor() const = 0;
//////////////////////////////////////////////////////////////////////
};
