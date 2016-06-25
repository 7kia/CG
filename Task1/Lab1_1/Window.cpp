#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{
const glm::vec3 LIGHT_YELLOW = { 1.f, 1.f, 0.5f};
const glm::vec3 RED = {1, 0, 0};
const glm::vec3 ORANGE = {1.f, 0.5f, 0.f};
const glm::vec3 YELLOW = {1.f, 1.f, 0.f};
const glm::vec4 QUIET_GREEN = {0.f, 0.5f, 0.2f, 1.f};
}

CWindow::CWindow()
{
    {
        auto pLine = std::make_unique<CLine>();
		pLine->SetFirstPoint(glm::vec2(250.f, 250.f));
		pLine->SetSecondPoint(glm::vec2(250.f, 650.f));
		pLine->SetOutlineColor(RED);
		pLine->SetThikness(5.f);

		m_shedule.AddFunctionsGraphs(std::move(pLine));
    }
    {
		auto pRectagnle = std::make_unique<CRectangle>();
		pRectagnle->SetLeftTopPoint(glm::vec2(550.f, 550.f));
		pRectagnle->SetWidth(100.f);
		pRectagnle->SetHeight(250.f);
		pRectagnle->SetOutlineColor(YELLOW);

		m_shedule.AddFunctionsGraphs(std::move(pRectagnle));
	}
    SetBackgroundColor(QUIET_GREEN);
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    (void)deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);

    for (const auto &pShape : m_shedule.m_functionsGraphs)
    {
		pShape->Draw();
    }
}

///*
void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	/*
	    auto flowers = boost::adaptors::reverse(m_shapes);
    auto it = boost::find_if(flowers, [&](const auto &pFlower) {
        return pFlower->HitTest(pos);
    });
    if (it != flowers.end())
    {
        m_draggingFlower = it->get();
        m_dragOffset = pos - m_draggingFlower->GetPosition();
    }

	*/
}

void CWindow::OnDragMotion(const glm::vec2 &pos)
{
	/*
    if (m_draggingFlower)
    {
        m_draggingFlower->SetPosition(pos - m_dragOffset);
    }
	*/
}

void CWindow::OnDragEnd(const glm::vec2 &pos)
{
	/*
    if (m_draggingFlower)
    {
        m_draggingFlower->SetPosition(pos - m_dragOffset);
        m_draggingFlower = nullptr;
    }
	*/
}

//*/

void CWindow::SetupView(const glm::ivec2 &size)
{
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const glm::mat4 matrix = glm::ortho<float>(0.f, static_cast<float>(size.x), static_cast<float>(size.y), 0.f);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
