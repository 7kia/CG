#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

CWindow::CWindow()
	: m_shedule(WINDOW_WIDTH, WINDOW_HEIGTH)
{
    
    {
		auto pFunctionGraph = std::make_unique<CLimitFunction>();

		pFunctionGraph->SetOrigin(glm::vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGTH / 2.f));
		pFunctionGraph->SetStart(-10.f);
		pFunctionGraph->SetEnd(10.f);
		pFunctionGraph->SetOutlineColor(Colors::YELLOW);

		m_shedule.AddFunctionsGraphs(std::move(pFunctionGraph));
	}
	{
		auto pFunctionGraph = std::make_unique<CArchimedeanSpiral>();

		pFunctionGraph->SetOrigin(glm::vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGTH / 2.f));
		pFunctionGraph->SetStart(0.f);
		pFunctionGraph->SetEnd(4.f * M_PI);
		pFunctionGraph->SetOutlineColor(Colors::RED);

		m_shedule.AddFunctionsGraphs(std::move(pFunctionGraph));
	}
    SetBackgroundColor(Colors::QUIET_GREEN);
}


void CWindow::OnUpdateWindow(float deltaSeconds)
{
    (void)deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);

	m_shedule.SetSize(size.x, size.y);
	m_shedule.Redraw();	
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
