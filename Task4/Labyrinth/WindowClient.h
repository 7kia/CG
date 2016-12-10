#pragma once
#include "AbstractWindowClient.h"
#include "Material\ShaderProgram.h"
#include "World\World.h"

#include <vector>

class CWindowClient : public CAbstractWindowClient
{
public:
    CWindowClient(CWindow &window);

protected:
    // IWindowClient interface
	void OnWindowInit(const glm::ivec2 &size) override;
	void OnUpdateWindow(float deltaSeconds) override;

	void OnKeyDown(const SDL_KeyboardEvent &) override;
    void OnKeyUp(const SDL_KeyboardEvent &) override;

private:
    void SetupView(const glm::ivec2 &size);

    CShaderProgram m_programPhong;
	CWorld m_world;
};
