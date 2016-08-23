#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // включаем систему освещения
    glEnable(GL_LIGHTING);

	// включаем текстурирование в старом стиле (OpenGL 1.1)
	glEnable(GL_TEXTURE_2D);

}

// включает смешивание цветов
// перед выводом полупрозрачных тел
void enableBlending()
{
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// отключает смешивание цветов
// перед выводом непрозрачных тел
void disableBlending()
{
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

float GetSincFromXY(float x, float y)
{
    const float radius = std::hypotf(x, y);
    if (radius < std::numeric_limits<float>::epsilon())
    {
        return 1;
    }
    return sinf(radius) / radius;
}

// MobiusStrip
float GetXMobiusStrip(float U, float V)
{
	return (1.f + (V / 2.f * cosf(U / 2.f))) * cosf(U);
}

float GetYMobiusStrip(float U, float V)
{
	return (1.f + (V / 2.f * cosf(U / 2.f))) * sinf(U);
}

float GetZMobiusStrip(float U, float V)
{
	return V / 2.f * sinf(U / 2.f);
}

const float r = 1.f;
// KleinBottle
float GetXKleinBottle(float U, float V)
{
	return 6.f * cosf(1.f + sinf(U)) + 4.f * r * (1.f - cosf(U / 2.f)) * cosf(U) * cosf(V);
}

float GetYKleinBottle(float U, float V)
{
	return 16.f * sinf(U) + 4.f * r * (1.f - cosf(U / 2.f)) * sinf(U) * cosf(V);
}

float GetZKleinBottle(float U, float V)
{
	return 4.f * r * (1.f - cosf(U / 2.f)) * sinf(V);
}

}

CWindow::CWindow()
{
    SetBackgroundColor(WindowSpace::BLACK);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();

	m_world.CreateScene();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_world.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
	m_world.Draw();
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

    // Матрица вида возвращается камерой и составляет
    // начальное значение матрицы GL_MODELVIEW.
    glLoadMatrixf(glm::value_ptr(m_world.GetCamera()->GetViewTransform()));

    // Матрица перспективного преобразования вычисляется функцией
    // glm::perspective, принимающей угол обзора, соотношение ширины
    // и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
    const float fieldOfView = glm::radians(70.f);
    const float aspect = float(size.x) / float(size.y);
    const float zNear = 0.01f;
    const float zFar = 100.f;
    const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
}

void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
    m_world.OnKeyDown(event);
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_world.OnKeyUp(event);
}
