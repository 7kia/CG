#include "stdafx.h"
#include "Shedule.h"

static const float						THIKNESS_LINES = 3;
static const float						ARROW_WIDTH = 3;
static const float						ARROW_HEIGTH = 25;


CShedule::CShedule(unsigned int width, unsigned int height)
	: m_windowWidth(float(width))
	, m_windowHeigth(float(height))
{
}

CShedule::~CShedule()
{
}

void CShedule::Draw() const
{
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