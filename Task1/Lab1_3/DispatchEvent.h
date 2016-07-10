#pragma once

#include "AbstractWindow.h"

class IInputEventAcceptor;
namespace sdl
{
// Совершает диспетчеризацию событий SDL по категориям.
void DispatchEvent(const SDL_Event & event, IInputEventAcceptor & acceptor);
}

// Принимает события SDL, разделённые по категориям.
// Деление условное и может быть изменено.
class IInputEventAcceptor
{
//////////////////////////////////////////////////////////////////////
// Methods
public:
    virtual ~IInputEventAcceptor() = default;

    virtual void OnDragBegin(const glm::vec2 &pos) { (void)pos; }
    virtual void OnDragMotion(const glm::vec2 &pos) { (void)pos; }
    virtual void OnDragEnd(const glm::vec2 &pos) { (void)pos; }
	virtual void OnDragBegin(const SDL_KeyboardEvent & event, const glm::vec2 & position) 
	{
		(void)event;
		(void)position;
	}
    virtual void OnKeyUp(const SDL_KeyboardEvent & event
						, const glm::vec2 & position) 
	{
		(void)event;
		(void)position;
	}
	virtual void OnKeyDown(const SDL_KeyboardEvent & event
		, const glm::vec2 & position)
	{
		(void)event;
		(void)position;
	}
//////////////////////////////////////////////////////////////////////
};

// Окно, совершающее диспетчеризацию событий SDL
class CAbstractInputControlWindow
        : public CAbstractWindow
        , public IInputEventAcceptor
{
//////////////////////////////////////////////////////////////////////
// Methods
protected:
    void OnWindowEvent(const SDL_Event &event) final
    {
        sdl::DispatchEvent(event, *this);
    }
//////////////////////////////////////////////////////////////////////
};
