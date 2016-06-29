#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

CWindow::CWindow()
	: m_shedule(WINDOW_WIDTH, WINDOW_HEIGTH)
{
	{
		auto pParcticle = std::make_unique<CParticle>();

		pParcticle->SetSign(true);

		pParcticle->SetOrigin(glm::vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGTH / 2.f));
		pParcticle->SetPosition(glm::vec2(0.f, 0.f));
		m_shedule.AddParcticle(std::move(pParcticle));
	}
	{
		auto pParcticle = std::make_unique<CParticle>();

		pParcticle->SetSign(false);
		pParcticle->SetOrigin(glm::vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGTH / 2.f));
		pParcticle->SetPosition(glm::vec2(100.f, 50.f));
		m_shedule.AddParcticle(std::move(pParcticle));
	}

	auto pEmitter = std::make_unique<CParticleEmitter>();
	pEmitter->SetPosition({ 0, 600 });
	pEmitter->SetAngleRange(0.7f * float(M_PI), 0.9f * float(M_PI));
	pEmitter->SetEmitIntervalRange(0.04f, 0.12f);
	pEmitter->SetLifetimeRange(10.f, 20.f);
	pEmitter->SetRadiusRange(40.f, 75.f);
	pEmitter->SetSpeedRange(8.f, 15.f);
	m_system.SetEmitter(std::move(pEmitter));

    SetBackgroundColor(Colors::GRAY);
}


void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_system.Advance(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);

	m_shedule.SetSize(size.x, size.y);
	m_shedule.Redraw();	

	m_system.Draw();

}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	auto flowers = boost::adaptors::reverse(m_shedule.m_particles);
	auto it = boost::find_if(flowers, [&](const auto &pFlower) {
		return pFlower->HitTest(pos);
	});
	if (it != flowers.end())
	{
		m_draggingParticle = it->get();
		m_dragOffset = pos - m_draggingParticle->GetPosition();
	}

}

void CWindow::OnDragMotion(const glm::vec2 &pos)
{
    if (m_draggingParticle)
    {
        m_draggingParticle->SetPosition(pos - m_dragOffset);
    }
}

void CWindow::OnDragEnd(const glm::vec2 &pos)
{
    if (m_draggingParticle)
    {
        m_draggingParticle->SetPosition(pos - m_dragOffset);
        m_draggingParticle = nullptr;
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
