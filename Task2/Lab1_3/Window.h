#pragma once
#include "DispatchEvent.h"
#include "Shape/Shapes.h"
#include "Decorators\Decorators.h"
#include "Camera.h"
#include "Lights.h"
#include "Material\PhongMaterial.h"
#include <vector>

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 &size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

    // IInputEventAcceptor interface
    void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
    void SetupView(const glm::ivec2 &size);

	std::vector<IBodyUniquePtr>		m_opaqueBodies;
	std::vector<IBodyUniquePtr>		m_transparentBodies;

	CTexture2DUniquePtr m_pEarthTexture;

    CPhongModelMaterial m_material;// TODO : transfer
    CCamera m_camera;
    CDirectedLightSource m_sunlight;
};
