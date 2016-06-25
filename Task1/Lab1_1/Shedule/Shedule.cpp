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
	/*
	// Arrow for y-axis
	auto pLeftFirstPart = GetPartArrow();
	pLeftFirstPart->SetLeftTopPoint(glm::vec2((m_windowWidth - THIKNESS_LINES * 8) / 2.f, (m_windowHeigth - THIKNESS_LINES * 8) / 2.f));
	pLeftFirstPart->SetRotate(ARROW_ANGLE);
	m_coordinateSystem.push_back(std::move(pLeftFirstPart));

	
	auto pRightFirstPart = GetPartArrow();
	pRightFirstPart->SetLeftTopPoint(glm::vec2((m_windowWidth - THIKNESS_LINES * 8) / 2.f, (m_windowHeigth - THIKNESS_LINES * 8) / 2.f));
	pRightFirstPart->SetRotate(-ARROW_ANGLE);
	m_coordinateSystem.push_back(std::move(pRightFirstPart));
	// Arrow for x-axis
	auto pLeftPart = GetPartArrow();
	pLeftPart->SetLeftTopPoint(glm::vec2((m_windowWidth + THIKNESS_LINES) / 2.f, 0.f));
	pLeftPart->SetRotate(ARROW_ANGLE);
	m_coordinateSystem.push_back(std::move(pLeftPart));

	auto pRightPart = GetPartArrow();
	pRightPart->SetLeftTopPoint(glm::vec2((m_windowWidth + THIKNESS_LINES) / 2.f, 0.f));
	pRightPart->SetRotate(-ARROW_ANGLE);
	m_coordinateSystem.push_back(std::move(pRightPart));


	*/
}

std::unique_ptr<CRectangle> CShedule::GetPartArrow()
{
	auto pPart = std::make_unique<CRectangle>();
	pPart->SetWidth(ARROW_WIDTH);
	pPart->SetHeight(ARROW_HEIGTH);
	pPart->SetOutlineColor(Colors::BLACK);

	return pPart;
}

std::unique_ptr<CRectangle> CShedule::GetDivision()
{
	auto pPart = std::make_unique<CRectangle>();
	pPart->SetWidth(DIVISION_WIDTH);
	pPart->SetHeight(DIVISION_HEIGTH);
	pPart->SetOutlineColor(Colors::BLACK);

	return pPart;
}

void CShedule::CreateDivisions()
{
	AddListDivisions(glm::vec2(SCALE_FACTOR, 0.f), 0.f);
	AddListDivisions(glm::vec2(-SCALE_FACTOR, 0.f), 0.f);

	AddListDivisions(glm::vec2(0.f, SCALE_FACTOR), 0.f);
	AddListDivisions(glm::vec2(0.f, -SCALE_FACTOR), 0.f);

}

void CShedule::AddListDivisions(const glm::vec2 & shift, float rotate)
{
	glm::vec2 startPosition = glm::vec2(m_windowWidth / 2.f, m_windowHeigth / 2.f);

	glm::vec2 position = startPosition + shift;
	for (size_t amountDivisions = 0; amountDivisions < AMOUNT_DIVISIONS; ++amountDivisions)
	{
		auto pDivision = GetDivision();
		pDivision->SetLeftTopPoint(position.x, position.y + SHIFT_DIVISION);
		pDivision->SetRotate(rotate);
		m_coordinateSystem.push_back(std::move(pDivision));

		position += shift;
	}
}
