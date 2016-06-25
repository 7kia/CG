#include "stdafx.h"
#include "Shedule.h"


CShedule::CShedule(unsigned int width, unsigned int height)
	: m_windowWidth(width)
	, m_windowHeigth(height)
{
	CreateAxis();
	CreateArrows();
	CreateDivisions();
}

CShedule::~CShedule()
{
}

void CShedule::Draw() const
{
	for (const auto &pShape : m_coordinateSystem)
	{
		pShape->Draw();
	}

	for (const auto &pShape : m_functionsGraphs)
	{
		pShape->Draw();
	}
}

void CShedule::Redraw() const
{
	for (auto & graph : m_functionsGraphs)
	{
		graph->Redraw();
	}
}

bool CShedule::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

void CShedule::AddFunctionsGraphs(std::shared_ptr<CShape> graph)
{
	m_functionsGraphs.push_back(graph);
}

void CShedule::CreateAxis()
{
	auto pXAxis = std::make_unique<CRectangle>();
	pXAxis->SetLeftTopPoint(glm::vec2(0.f, (m_windowHeigth + THIKNESS_LINES) / 2.f));
	pXAxis->SetWidth(m_windowWidth);
	pXAxis->SetHeight(THIKNESS_LINES);
	pXAxis->SetOutlineColor(Colors::BLACK);

	m_coordinateSystem.push_back(std::move(pXAxis));

	// Y-axis
	auto pYAxis = std::make_unique<CRectangle>();
	pYAxis->SetLeftTopPoint(glm::vec2((m_windowWidth + THIKNESS_LINES) / 2.f, 0.f));
	pYAxis->SetWidth(THIKNESS_LINES);
	pYAxis->SetHeight(m_windowHeigth);
	pYAxis->SetOutlineColor(Colors::BLACK);

	m_coordinateSystem.push_back(std::move(pYAxis));
}

void CShedule::CreateArrows()
{
}

void CShedule::CreateDivisions()
{
}
