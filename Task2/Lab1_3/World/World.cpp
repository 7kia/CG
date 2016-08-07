#include "stdafx.h"
#include "World.h"

CWorld::CWorld()
	: IDrawable()
	, IInputEventAcceptor()
	, IUpdatable()
	, m_player(glm::vec3(0.f, 0.5f, 1.f), PlayerCameraSpace::PLAYER_DIRECTION)//m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
	, m_sunlight(GL_LIGHT0)
{
	m_material.SetAmbient(WorldSpace::YELLOW_RGBA);
	m_material.SetDiffuse(WorldSpace::YELLOW_RGBA);
	m_material.SetSpecular(WorldSpace::FADED_WHITE_RGBA);
	m_material.SetShininess(WorldSpace::MATERIAL_SHININESS);

	m_sunlight.SetDirection(WorldSpace::SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WorldSpace::WHITE_RGBA);
	m_sunlight.SetAmbient(0.1f * WorldSpace::WHITE_RGBA);
	m_sunlight.SetSpecular(WorldSpace::WHITE_RGBA);
}

void CWorld::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_camera.OnKeyDown(event);
	m_player.m_pController->
}

void CWorld::OnKeyUp(const SDL_KeyboardEvent & event)
{
	m_camera.OnKeyUp(event);
}

void CWorld::Draw() const
{
	m_sunlight.Setup();
	m_material.Setup();

	for (const IBodyUniquePtr &pBody : m_opaqueBodies)
	{
		pBody->Draw();
	}

	//enableBlending();
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Draw();
	}
	//disableBlending();
}

void CWorld::Update(float deltaTime)
{
	m_camera.Update(deltaTime);
	for (const IBodyUniquePtr &pBody : m_opaqueBodies)
	{
		pBody->Update(deltaTime);
	}
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Update(deltaTime);
	}
}

CAbcstartCamera * CWorld::GetPlayerCamera()
{
	return dynamic_cast<CAbcstartCamera*>(&m_camera);
}

void CWorld::CreateScene()
{
	{
		IBodyUniquePtr pSphere = std::make_unique<CIdentitySphere>(SphereSpace::SPHERE_PRECISION, SphereSpace::SPHERE_PRECISION);

		auto pAnimate = std::make_unique<CAnimatedShapeDecorator>();
		pAnimate->SetChild(std::move(pSphere));

		auto pTexture = std::make_unique<CTexture2DShapeDecorator>();
		pTexture->SetChild(std::move(pAnimate));
		pTexture->SetTexture(WorldSpace::EARTH_TEX_PATH);

		m_opaqueBodies.emplace_back(std::move(pTexture));
	}
	{
		IBodyUniquePtr pSphere = std::make_unique<CIdentitySphere>(SphereSpace::SPHERE_PRECISION, SphereSpace::SPHERE_PRECISION);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 1.5f, 0.f, 0.f }));
		pTransform->SetChild(std::move(pSphere));

		m_opaqueBodies.emplace_back(std::move(pTransform));

	}
}
