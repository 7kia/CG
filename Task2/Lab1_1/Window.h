#pragma once
#include "DispatchEvent.h"
#include "Shape/Shape.h"
#include "Camera.h"
#include "Lights.h"
#include <vector>

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();
//////////////////////////////////////////////////////////////////////
// Methods
protected:
	//--------------------------------------------
	// CAbstractWindow interface
    void							OnWindowInit(const glm::ivec2 &size) override;
    void							OnUpdateWindow(float deltaSeconds) override;
    void							OnDrawWindow(const glm::ivec2 &size) override;
	//--------------------------------------------
    // IInputEventAcceptor interface
    void							OnKeyDown(const SDL_KeyboardEvent &) override;
    void							OnKeyUp(const SDL_KeyboardEvent &) override;
	//--------------------------------------------
//////////////////////////////////////////////////////////////////////
// Methods
private:
    void							InitBodies();
    void							SetupView(const glm::ivec2 &size);
//////////////////////////////////////////////////////////////////////
// Data
private:
    std::vector<IBodyUniquePtr>		m_opaqueBodies;
    std::vector<IBodyUniquePtr>		m_transparentBodies;
    CCamera							m_camera;
    CDirectedLightSource			m_sunlight;
};
