#pragma once
#include <glm/vec3.hpp>

class IDrawable
{
public:
	virtual	~IDrawable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			Draw() const = 0;

	// By default might will do nothing
	// TODO : see vec3 or vec2 use
	virtual bool			HitTest(const glm::vec3 &point) const { (void)point; return false; };
};