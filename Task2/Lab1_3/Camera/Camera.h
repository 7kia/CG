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
	virtual				glm::mat4 GetViewTransform() const = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:

};
