#pragma once

#include "Mixin/Drawable.h"
#include "Mixin/Updatable.h"

#include "DispatchEvent.h"
#include "3DShape\3DShapes.h"
#include "Camera\Cameras.h"
#include "Lights.h"
#include "..\Material\PhongMaterial.h"

#include "Actor\Player\HavePlayer.h"
#include "Actor\LifeObjects\HaveLifeObject.h"
#include "World\HaveFactionSystem.h"
#include "Wall\HaveWallTypes.h"
#include "HavePhysicalWorld.h"
#include "Map.h"

#include <vector>

namespace WorldSpace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const float MATERIAL_SHININESS = 30.f;
	const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
	const glm::vec4 GRAY_RGBA = { 0.1f, 0.1f, 0.1f, 1 };
	const glm::vec4 FADED_WHITE_RGBA = { 0.3f, 0.3f, 0.3f, 1.f };
	const glm::vec4 YELLOW_RGBA = { 1, 1, 0, 1 };
	const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };
	const float CAMERA_INITIAL_ROTATION = 0;
	const float CAMERA_INITIAL_DISTANCE = 5.f;
}

class CWorld
	: public CActor
	, public IInputEventAcceptor
	, public CHaveLifeObjects
	, public CHaveWallTypes
	, public CHavePhysicalWorld
	, public CHavePlayer
	, public CHaveFactionSystem
{
public:
	CWorld();

	enum class GameState
	{
		Play
		, Pause
		, Defeat
		, Victory
	};
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


	//--------------------------------------------
	// Behavior // TOOD : trasfer to Behavior
	void UpdateBehavior();


	glm::vec3				GetDirectionToObject(CHave3DPosition & to, CHave3DPosition & from);

	void DefineNeedAttackEnemy(CLifeObject & object, CLifeObject & enemy);

	void ActivateActiveWeapons();

	//--------------------------------------------


	void							SwitchPlayState();
	void							CreateScene();

	void							CreateShoot(const glm::vec3 & position
												, const glm::vec3 & direction
												, const CWeapon & weapon
												);


	ActorSharedPtr					CreateLifeObject(CLifeObjectType::Id id
													, const glm::vec3 & position
													, const glm::vec3 & direction);
	void							CreatePlayer(const glm::vec3 & position
												, const glm::vec3 & direction);


private:

	

	void							DeleteDeathObject();
//////////////////////////////////////////////////////////////////////
// Data
private:
	CMap							m_map;
	std::vector<ActorSharedPtr>		m_actors;
	GameState						m_gameState = GameState::Play;
	CPhongModelMaterial				m_material;
};