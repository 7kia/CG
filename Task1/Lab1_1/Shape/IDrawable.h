#include <SDL2/SDL_rect.h>// TODO : ask why if there sdl2/sdl.h then error with sdl_main8
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/noncopyable.hpp>

class IDrawable
{
public:
	virtual void			Draw() const = 0;

	// TODO: Redefine in heir after CDrawable \/
	virtual void			Redraw() const = 0;
	virtual bool			HitTest(const glm::vec2 &point) const = 0;// TODO : might will be neccessary

protected:
	virtual void			DeleteList() = 0;
};