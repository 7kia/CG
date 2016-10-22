#pragma once
#include "libchapter3.h"
#include "Shape/FunctionSurface.h"
#include "EarthProgramContext.h"
#include "WaveContext.h"
#include "TwistValueController.h"

#include <vector>

class CWindowClient
        : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
    void OnUpdateWindow(float deltaSeconds) override;
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
    void CheckOpenGLVersion();
    void UpdateRotation(float deltaSeconds);
    void SetupView(const glm::ivec2 &size);
    void SetupLight0();

    // Данный VAO будет объектом по-умолчанию.
    // Его привязка должна произойти до первой привязки VBO.
    //  http://stackoverflow.com/questions/13403807/
    CArrayObject m_defaultVAO;

	CSolidFunctionSurface m_surface;


    CCamera m_camera;
    CDirectedLightSource m_sunlight;
    CWaveProgramContext m_programContext;// TOOD : rename

	bool m_programEnabled = true;
	CTwistValueController m_twistController;

};
