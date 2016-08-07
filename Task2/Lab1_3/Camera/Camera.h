#pragma once

#include <glm/fwd.hpp>
#include <SDL2/SDL_events.h>
#include <boost/noncopyable.hpp>
#include <set>
#include <glm/gtx/rotate_vector.hpp>


#include "../Mixin/Updatable.h"

namespace CameraSpace
{
	// TODO : see need transfer
	static bool ShouldTrackKeyPressed(const SDL_Keysym &key)
	{
		switch (key.sym)
		{
		case SDLK_LEFT:
		case SDLK_RIGHT:
		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_w:
		case SDLK_a:
		case SDLK_s:
		case SDLK_d:
			return true;
		}
		return false;
	}

}

class CAbcstartCamera{
public:
	CAbcstartCamera();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	// TODO
	// Need coordinate with IInputEventAcceptor
	// two low methods is common for all cameras
	bool				OnKeyDown(const SDL_KeyboardEvent &event);
	bool				OnKeyUp(const SDL_KeyboardEvent &event);

	virtual				glm::mat4 GetViewTransform() const = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:

};
