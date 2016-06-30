#include "stdafx.h"
#include "Shedule.h"

static const float						THIKNESS_LINES = 3;
static const float						ARROW_WIDTH = 3;
static const float						ARROW_HEIGTH = 25;


CShedule::CShedule(unsigned int width, unsigned int height)
	: m_windowWidth(float(width))
	, m_windowHeigth(float(height))
{
	CreateSystem();
}

CShedule::~CShedule()
{
	CreateSystem();
}

void CShedule::Draw() const
{
	m_system.Draw();

	for (const auto &pShape : m_gui)
	{
		pShape->Draw();
	}

	for (const auto &pShape : m_particles)
	{
		pShape->Draw();
	}
}

void CShedule::Redraw() const
{
	m_system.Redraw();

	for (const auto &pShape : m_gui)
	{
		pShape->Redraw();
	}

	for (auto & graph : m_particles)
	{
		graph->Redraw();
	}
}

bool CShedule::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}

void CShedule::SetSize(unsigned int width, unsigned int height)
{
	m_windowWidth = float(width);
	m_windowHeigth = float(height);


	for (auto & graph : m_particles)
	{
		graph->SetOrigin(glm::vec2(width / 2.f, height / 2.f));
	}
}

void CShedule::AddParcticle(std::unique_ptr<CParticle> graph)
{
	m_particles.push_back(std::move(graph));
}

void CShedule::Advance(float dt)
{
	m_system.Advance(dt);
}

void CShedule::CreateSystem()
{
	auto pEmitter = std::make_unique<CParticleEmitter>();
	pEmitter->SetPosition(glm::vec2(m_windowWidth / 2.f, m_windowHeigth / 2.f));
	pEmitter->SetAngleRange(0.7f * float(M_PI), 0.9f * float(M_PI));
	pEmitter->SetEmitIntervalRange(0.04f, 0.12f);
	pEmitter->SetLifetimeRange(3.f, 8.f);
	pEmitter->SetRadiusRange(200.f, 600.f);
	pEmitter->SetSpeedRange(80.f, 150.f);

	m_system.SetEmitter(std::move(pEmitter));
}
