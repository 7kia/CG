#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: IDrawable()
	, IInputEventAcceptor()
	, IUpdatable()
	, CHaveWallTypes()
	, m_sunlight(GL_LIGHT0)
	, m_player(glm::vec3(0.f, 0.5f, 1.f), PlayerCameraSpace::PLAYER_DIRECTION)
	, m_map("map.txt", this)
{
	m_material.SetAmbient(WorldSpace::WHITE_RGBA);
	m_material.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_material.SetSpecular(WorldSpace::FADED_WHITE_RGBA);
	m_material.SetShininess(WorldSpace::MATERIAL_SHININESS);

	m_sunlight.SetDirection(WorldSpace::SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_sunlight.SetAmbient(0.f * WorldSpace::WHITE_RGBA);
	m_sunlight.SetSpecular(WorldSpace::WHITE_RGBA);
}

void CWorld::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_player.m_pController->OnKeyDown(event);
}

void CWorld::OnKeyUp(const SDL_KeyboardEvent & event)
{
	m_player.m_pController->OnKeyUp(event);
}

void CWorld::Draw() const
{
	m_sunlight.Setup();
	m_material.Setup();

	m_player.Draw();

	for (const IBodyUniquePtr &pBody : m_opaqueBodies)
	{
		pBody->Draw();
	}
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Draw();
	}
	m_map.Draw();
}

void CWorld::Update(float deltaTime)
{
	m_player.Update(deltaTime);
	for (const IBodyUniquePtr &pBody : m_opaqueBodies)
	{
		pBody->Update(deltaTime);
	}
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Update(deltaTime);
	}

	m_map.Update(deltaTime);
}

CAbcstartCamera * CWorld::GetCamera()
{
	return m_player.GetCamera();
}

void CWorld::CreateScene()
{
	CreateWallTypes();

	/*
		{
		auto pWall = std::make_unique<CWallView>();
		pWall->SetType(GetWallType(1));

		auto pAnimate = std::make_unique<CAnimatedShapeDecorator>();
		pAnimate->SetChild(std::move(pWall));

		m_opaqueBodies.emplace_back(std::move(pAnimate));

	}
	{
		IBodyUniquePtr pSphere = std::make_unique<CIdentity3DSphere>(SphereSpace::SPHERE_PRECISION, SphereSpace::SPHERE_PRECISION);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 1.5f, 0.f, 0.f }));
		pTransform->SetChild(std::move(pSphere));

		m_opaqueBodies.emplace_back(std::move(pTransform));

	}

	*/

}
