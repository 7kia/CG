#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{
const glm::vec4 BLACK = {0, 0, 0, 1};
const float MATERIAL_SHININESS = 30.f;
const glm::vec4 WHITE_RGBA = {1, 1, 1, 1};
const glm::vec4 FADED_WHITE_RGBA = {0.3f, 0.3f, 0.3f, 1.f};
const glm::vec4 YELLOW_RGBA = {1, 1, 0, 1};
const glm::vec3 SUNLIGHT_DIRECTION = {-1.f, 0.2f, 0.7f};
const float CAMERA_INITIAL_ROTATION = 0;
const float CAMERA_INITIAL_DISTANCE = 5.f;

const char EARTH_TEX_PATH[] = "res/daily_earth.bmp";


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
    : m_camera(glm::vec3(0.f, 0.5f, 1.f), PlayerCameraSpace::PLAYER_DIRECTION)//m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
    , m_sunlight(GL_LIGHT0)
{
    SetBackgroundColor(BLACK);


    m_material.SetAmbient(YELLOW_RGBA);
    m_material.SetDiffuse(YELLOW_RGBA);
    m_material.SetSpecular(FADED_WHITE_RGBA);
    m_material.SetShininess(MATERIAL_SHININESS);

   
    m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
    m_sunlight.SetDiffuse(WHITE_RGBA);
    m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
    m_sunlight.SetSpecular(WHITE_RGBA);

}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();

	{
		IBodyUniquePtr pSphere = std::make_unique<CIdentitySphere>(SphereSpace::SPHERE_PRECISION, SphereSpace::SPHERE_PRECISION);

		auto pAnimate = std::make_unique<CAnimatedShapeDecorator>();
		pAnimate->SetChild(std::move(pSphere));

		auto pTexture = std::make_unique<CTexture2DShapeDecorator>();
		pTexture->SetChild(std::move(pAnimate));
		pTexture->SetTexture(EARTH_TEX_PATH);

		m_opaqueBodies.emplace_back(std::move(pTexture));
	}
	{
		IBodyUniquePtr pSphere = std::make_unique<CIdentitySphere>(SphereSpace::SPHERE_PRECISION, SphereSpace::SPHERE_PRECISION);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 1.5f, 0.f, 0.f }));
		pTransform->SetChild(std::move(pSphere));

		m_opaqueBodies.emplace_back(std::move(pTransform));

	}
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_camera.Update(deltaSeconds);
	for (const IBodyUniquePtr &pBody : m_opaqueBodies)
	{
		pBody->Update(deltaSeconds);
	}
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Update(deltaSeconds);
	}
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
	m_sunlight.Setup();
	m_material.Setup();

	//m_pEarthTexture->DoWhileBinded([&] {
		for (const IBodyUniquePtr &pBody : m_opaqueBodies)
		{
			pBody->Draw();
		}
	//});

		
	//enableBlending();
	for (const IBodyUniquePtr &pBody : m_transparentBodies)
	{
		pBody->Draw();
	}
	//disableBlending();
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

    // Матрица вида возвращается камерой и составляет
    // начальное значение матрицы GL_MODELVIEW.
    glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

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
    m_camera.OnKeyDown(event);
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
    m_camera.OnKeyUp(event);
}
