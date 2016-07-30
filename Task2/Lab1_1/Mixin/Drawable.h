#pragma once
#include <glm/vec3.hpp>
// TODO : see need the block
/*
#include <SDL2/SDL_rect.h>// TODO : ask why if there sdl2/sdl.h then error with sdl_main8
#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/noncopyable.hpp>

*/

class IDrawable
{
public:
	virtual	~IDrawable() = default;
//////////////////////////////////////////////////////////////////////
// Methods
public:
	virtual void			Draw() const = 0;

	// By default might will do nothing
	virtual bool			HitTest(const glm::vec3 &point) const { (void)point; };
};