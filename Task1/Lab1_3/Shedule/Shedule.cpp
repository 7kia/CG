#include "stdafx.h"
#include "Shedule.h"

static const float						THIKNESS_LINES = 3;
static const float						ARROW_WIDTH = 3;
static const float						ARROW_HEIGTH = 25;


CShedule::CShedule(unsigned int width, unsigned int height)
	: m_windowWidth(float(width))
	, m_windowHeigth(float(height))
	, m_system(float(width), float(height))
{
	CreateSystem();
}

CShedule::~CShedule()
{
	CreateSystem();
}

void CShedule::Redraw() const
{
	m_system.Redraw();

	for (const auto &pShape : m_gui)
	{
		pShape->Redraw();
	}

	for (auto & graph : m_system.m_shapes)
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

	m_system.SetPosition(glm::vec2(width / 2.f, height / 2.f));
}

void CShedule::AddParcticle(std::shared_ptr<CDrawable> graph)
{
	m_system.AddShape(std::move(graph));
}

void CShedule::Advance(float dt)
{
	m_system.Advance(dt);
}

void CShedule::CreateSystem()
{
	m_system.SetPosition(glm::vec2(0.f, 0.f));
	m_system.SetPlaceSize(glm::vec2(m_windowWidth, m_windowHeigth));
}

CPhysicalSystem & CShedule::GetPhysicSystem()
{
	return m_system;
}

bool CShedule::OnDragBegin(const glm::vec2 & position)
{
	return m_system.OnDragBegin(position);
}
