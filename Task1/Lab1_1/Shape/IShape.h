#pragma once

#include "CDrawable.h"

class IShape
{
public:
	virtual void			SetOutlineColor(const glm::vec3 &color) = 0;
	virtual glm::vec3		GetOutlineColor() const = 0;
};
