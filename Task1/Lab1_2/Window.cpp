#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

CWindow::CWindow()
	: m_shedule(WINDOW_WIDTH, WINDOW_HEIGTH)
{
	const glm::vec2 CENTER_WINODOW = glm::vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGTH / 2.f);
	
    SetBackgroundColor(Colors::GRAY);
}


void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_shedule.Advance(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);

	m_shedule.SetSize(size.x, size.y);
	m_shedule.Redraw();	
}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	auto particles = boost::adaptors::reverse(m_shedule.GetParticleSystem().m_particles);
	auto it = boost::find_if(particles, [&](const auto &pFlower) {
		return pFlower->HitTest(pos);
	});
	if (it != particles.end())
	{
		auto p = std::shared_ptr<CStaticParticle>(it->get());
		m_shedule.GetParticleSystem().m_draggingParticle._Reset(p);
		m_dragOffset = pos - Lock(m_shedule.GetParticleSystem().m_draggingParticle)->GetPosition();
	}
	else
	{
		Lock(m_shedule.GetParticleSystem().m_draggingParticle).reset();
	}

}

void CWindow::OnDragMotion(const glm::vec2 &pos)
{
    if (!m_shedule.GetParticleSystem().m_draggingParticle.expired())
    {
		m_shedule.GetParticleSystem().m_draggingParticle.lock()->SetPosition(pos - m_dragOffset);
    }
}

void CWindow::OnDragEnd(const glm::vec2 &pos)
{
    if (!m_shedule.GetParticleSystem().m_draggingParticle.expired())
    {
		Lock(m_shedule.GetParticleSystem().m_draggingParticle)->SetPosition(pos - m_dragOffset);
		m_shedule.GetParticleSystem().m_draggingParticle.reset();
    }
}

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
