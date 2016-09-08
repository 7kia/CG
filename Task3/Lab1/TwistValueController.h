#pragma once
#include <SDL2/SDL_events.h>

class CTwistValueController
{
//////////////////////////////////////////////////////////////////////
// Methods

public:
    void	Update(float deltaSeconds);
    bool	OnKeyDown(const SDL_KeyboardEvent &event);

    float	GetCurrentValue()const;
//////////////////////////////////////////////////////////////////////
// Data
private:
    float	m_currentTwistValue = 0;
    float	m_nextTwistValue = 0;
};
