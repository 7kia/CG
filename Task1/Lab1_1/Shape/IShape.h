#pragma once

#include <SDL2/SDL_rect.h>// TODO : ask why if there sdl2/sdl.h then error with sdl_main8
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/noncopyable.hpp>

class CDrawable
{
public:
	CDrawable() = default;
	virtual ~CDrawable();
public:

	void					Draw() const;

	// Redefine in heir \/
	virtual void			Redraw() const = 0;
	virtual bool			HitTest(const glm::vec2 &point) const = 0;// TODO : might will be neccessary
	//					/\/

protected:
	void					DeleteList();
	mutable unsigned		m_displayList = 0;

};

class IShape
	: public CDrawable
{
public:
	virtual void			SetOutlineColor(const glm::vec3 &color) = 0;
	virtual glm::vec3		GetOutlineColor() const = 0;

};
