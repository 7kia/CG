#include "stdafx.h"
#include "Camera.h"

CAbcstartCamera::CAbcstartCamera()
	: IUpdatable()
{
}

bool CAbcstartCamera::OnKeyDown(const SDL_KeyboardEvent &event)
{
    if (CameraSpace::ShouldTrackKeyPressed(event.keysym))
    {
        m_keysPressed.insert(unsigned(event.keysym.sym));
        return true;
    }
    return false;
}

bool CAbcstartCamera::OnKeyUp(const SDL_KeyboardEvent &event)
{
    if (CameraSpace::ShouldTrackKeyPressed(event.keysym))
    {
        m_keysPressed.erase(unsigned(event.keysym.sym));
        return true;
    }
    return false;
}
