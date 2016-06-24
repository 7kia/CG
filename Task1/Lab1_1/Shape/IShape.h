#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/noncopyable.hpp>

class IShape
{
public:
	virtual void			SetOutlineColor(const glm::vec3 &color) = 0;
	virtual glm::vec3		GetOutlineColor() const = 0;

	virtual void			Draw() const = 0;

	// Redefine in heir \/
	virtual void			Redraw() const = 0;
	virtual bool			HitTest(const glm::vec2 &point) const = 0;// TODO : might will be neccessary
	//					/\

private:
	virtual void			DeleteList() = 0;
};
