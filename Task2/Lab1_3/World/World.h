#pragma once

#include "../Mixin/Drawable.h"
#include "../Mixin/Updatable.h"

#include "..\DispatchEvent.h"
#include "..\3DShape\3DShapes.h"
#include "..\Decorators\Decorators.h"
#include "..\Camera\Cameras.h"
#include "..\Lights.h"
#include "..\Material\PhongMaterial.h"

#include "Player.h"
#include "Wall\HaveWallTypes.h"
#include "Map.h"

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

	const char BREAK_TEXTURE_PATH[] = "Resources/brick.bmp";
	const char PLANK_TEXTURE_PATH[] = "Resources/plank.bmp";

}

class CWorld
	: public IDrawable
	, public IInputEventAcceptor
	, public IUpdatable
	, public CHaveWallTypes
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

	CAbcstartCamera*				GetCamera();

	// TODO : do call_once
	void							CreateScene();
//////////////////////////////////////////////////////////////////////
// Data

private:
	std::vector<IBodyUniquePtr>		m_opaqueBodies;
	std::vector<IBodyUniquePtr>		m_transparentBodies;

	CPlayer							m_player;

	CMap							m_map;


	// Player can change camera
	bool							m_changePlayer = true;
	CPhongModelMaterial m_material;// TODO : transfer
	CDirectedLightSource m_sunlight;

};