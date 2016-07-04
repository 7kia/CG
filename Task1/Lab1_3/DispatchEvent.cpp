#include "stdafx.h"
#include "DispatchEvent.h"

namespace
{
glm::vec2 GetMousePosition(const SDL_MouseButtonEvent &event)
{
    return { event.x, event.y };
}

glm::vec2 GetMousePosition(const SDL_MouseMotionEvent &event)
{
    return { event.x, event.y };
}
}

void sdl::DispatchEvent(const SDL_Event &event, IInputEventAcceptor &acceptor)
{
	glm::vec2 mousePosition = GetMousePosition(event.button);
    switch (event.type)
    {
	case SDL_KEYDOWN:
		acceptor.OnDragBegin(event.key, mousePosition);
		break;
	case SDL_KEYUP:
		acceptor.OnKeyUp(event.key, mousePosition);
		break;
	case SDL_MOUSEBUTTONDOWN:
		acceptor.OnDragBegin(GetMousePosition(event.button));
		break;
	case SDL_MOUSEBUTTONUP:
		acceptor.OnDragEnd(GetMousePosition(event.button));
		break;
	case SDL_MOUSEMOTION:
		acceptor.OnDragMotion(GetMousePosition(event.motion));
		break;
    }
}
