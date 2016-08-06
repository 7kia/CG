#pragma once

#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"

#include "..\DispatchEvent.h"
#include "..\Shape\Shapes.h"
#include "..\Decorators\Decorators.h"
#include "..\Camera\Cameras.h"
#include "..\Lights.h"
#include "..\Material\PhongMaterial.h"
#include <vector>

namespace WorldSpace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const float MATERIAL_SHININESS = 30.f;
	const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
	const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
	const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
	const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };
	const float CAMERA_INITIAL_ROTATION = 0;
	const float CAMERA_INITIAL_DISTANCE = 5.f;

	const char EARTH_TEX_PATH[] = "res/daily_earth.bmp";

}

class CWorld
	: public IDrawable
	, public IInputEventAcceptor
	, public IUpdatable
{
public:
	CWorld();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IInputEventAcceptor
	void							OnKeyDown(const SDL_KeyboardEvent & event) override;
	void							OnKeyUp(const SDL_KeyboardEvent & event) override;
	//--------------------------------------------
	// IDrawable
	void							Draw() const override;
	//--------------------------------------------
	// IUpdatable
	void							Update(float deltaTime);
	//--------------------------------------------

	CAbcstartCamera*				GetPlayerCamera();

	// TODO : do call_once
	void							CreateScene();
//////////////////////////////////////////////////////////////////////
// Data

private:
	std::vector<IBodyUniquePtr>		m_opaqueBodies;
	std::vector<IBodyUniquePtr>		m_transparentBodies;

	CPhongModelMaterial m_material;// TODO : transfer
	CPlayerCamera m_camera;
	CDirectedLightSource m_sunlight;

};