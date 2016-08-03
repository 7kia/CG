#include "stdafx.h"
#include "Window.h"
#include "Shape/Shapes.h"
#include "Decorators/Decorators.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

using namespace CubeSpace;

namespace
{
const glm::vec4 BLACK = {0, 0, 0, 1};
const glm::vec4 WHITE_RGBA = {1, 1, 1, 1};
const glm::vec3 SUNLIGHT_DIRECTION = {-1.f, 0.2f, 0.7f};
const float CAMERA_INITIAL_ROTATION = 180.f;
const float CAMERA_INITIAL_DISTANCE = 5.f;

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

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // включаем систему освещения
    glEnable(GL_LIGHTING);

    // включаем применение цветов вершин как цвета материала.
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
}

CWindow::CWindow()
    : m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
    , m_sunlight(GL_LIGHT0)
{
    SetBackgroundColor(BLACK);
    InitBodies();

    m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
    m_sunlight.SetDiffuse(WHITE_RGBA);
    m_sunlight.SetAmbient(0.1f * WHITE_RGBA);
    m_sunlight.SetSpecular(WHITE_RGBA);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
    (void)size;
    SetupOpenGLState();
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
    for (const IBodyUniquePtr &pBody : m_opaqueBodies)
    {
        pBody->Draw();
    }
    enableBlending();
    for (const IBodyUniquePtr &pBody : m_transparentBodies)
    {
        pBody->Draw();
    }
    disableBlending();
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

void CWindow::InitBodies()
{
    const glm::vec4 YELLOW = { 1.f, 1.f, 0.f, Colors::DEFAULT_ALPHA};
    const glm::vec4 ORANGE = { 1.f, 0.5f, 0.f, Colors::DEFAULT_ALPHA };
    const glm::vec4 PINK = { 1.f, 0.3f, 0.3f, Colors::DEFAULT_ALPHA };
    const glm::vec4 RED = {1.f, 0.f, 0.f, Colors::DEFAULT_ALPHA };
    const glm::vec4 GREEN = {0.f, 1.f, 0.f, Colors::DEFAULT_ALPHA };
    const glm::vec4 BLUE = {0.f, 0.f, 1.f, Colors::DEFAULT_ALPHA };
    const glm::vec4 RED_RGBA = {1, 0, 0, Colors::DEFAULT_ALPHA };

	/*

    {
        auto pCube = std::make_unique<CIdentityCube>();
        pCube->SetAlpha(0.7f);
        pCube->SetFaceColor(CubeFace::Top, YELLOW);
        pCube->SetFaceColor(CubeFace::Bottom, YELLOW);
        pCube->SetFaceColor(CubeFace::Left, ORANGE);
        pCube->SetFaceColor(CubeFace::Right, ORANGE);
        pCube->SetFaceColor(CubeFace::Front, PINK);
        pCube->SetFaceColor(CubeFace::Back, PINK);

        auto pTransform = std::make_unique<CTransformShapeDecorator>();
        pTransform->SetTransform(glm::translate(glm::mat4(), {-2.5f, 0.f, 0.f}));
        pTransform->SetChild(std::move(pCube));
        m_transparentBodies.emplace_back(std::move(pTransform));
    }
    {
        auto pCube = std::make_unique<CIdentityCube>();
        pCube->SetAlpha(0.7f);
        pCube->SetFaceColor(CubeFace::Top, RED);
        pCube->SetFaceColor(CubeFace::Bottom, RED);
        pCube->SetFaceColor(CubeFace::Left, GREEN);
        pCube->SetFaceColor(CubeFace::Right, GREEN);
        pCube->SetFaceColor(CubeFace::Front, BLUE);
        pCube->SetFaceColor(CubeFace::Back, BLUE);

        auto pAnimator = std::make_unique<CAnimatedShapeDecorator>();
        pAnimator->SetChild(std::move(pCube));

        auto pTransform = std::make_unique<CTransformShapeDecorator>();
        pTransform->SetTransform(glm::translate(glm::mat4(), {2.5f, 0.f, 0.f}));
        pTransform->SetChild(std::move(pAnimator));

        m_transparentBodies.emplace_back(std::move(pTransform));
    }
    {
        auto pTetrahedron = std::make_unique<CTetrahedron>();
        pTetrahedron->SetFaceColor(RED_RGBA);
        m_opaqueBodies.emplace_back(std::move(pTetrahedron));
    }
	{
		auto pTriangle = std::make_unique<CTriangle>();
		pTriangle->SetFaceColor(RED_RGBA);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 0.f, 0.f, 2.5f }));
		pTransform->SetChild(std::move(pTriangle));


		m_opaqueBodies.emplace_back(std::move(pTransform));
	}
	{
		auto pRectangle = std::make_unique<CRectangle>();
		pRectangle->SetFaceColor(RED_RGBA);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		//pTransform->SetTransform();

		const glm::mat4 translate = glm::translate(glm::mat4(), { 0.f, 0.5f, 2.5f });

		pTransform->SetTransform(glm::rotate(translate, 45.f, { 0.f, 2.5f, 0.f }));
		pTransform->SetChild(std::move(pRectangle));


		m_opaqueBodies.emplace_back(std::move(pTransform));
	}
	
	{
		auto pPentagon = std::make_unique<CPentagon>();
		pPentagon->SetFaceColor(YELLOW);

		std::array<glm::vec3, 6> points;
		points[0] = { 1.248f, -0.771f, 0.f };
		points[1] = { -1.547, 0.634f, 0.f };
		points[2] = { -0.969f, 0.991f, 0.934f };
		points[3] = { -0.035f, 1.568f, 0.557f };
		points[4] = { -0.035f, 1.568f, -0.577f };
		points[5] = { -0.969f, 0.991f, -0.934f };

		for (size_t index = 0; index < 6; ++index)
		{
			pPentagon->SetVertex(index, points[index]);
		}


		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform();

		const glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3());//{ 0.5f, 0.75f, 2.0f }

		pTransform->SetTransform(translate);
		pTransform->SetChild(std::move(pPentagon));


		m_opaqueBodies.emplace_back(std::move(pTransform));
	}

	*/
	{
		auto pDodecahedron = std::make_unique<CDodecahedron>();
		pDodecahedron->SetFaceColor(RED);

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 0.f, 0.0f, 1.5f }));
		pTransform->SetChild(std::move(pDodecahedron));


		m_opaqueBodies.emplace_back(std::move(pTransform));
	}
	{
		auto pDodecahedron = std::make_unique<CDodecahedron>();
		pDodecahedron->SetFaceColor(GREEN);

		auto pAnimator = std::make_unique<CAnimatedShapeDecorator>();
		pAnimator->SetChild(std::move(pDodecahedron));

		auto pTransform = std::make_unique<CTransformShapeDecorator>();
		pTransform->SetTransform(glm::translate(glm::mat4(), { 0.f, 0.f, -1.5f }));
		pTransform->SetChild(std::move(pAnimator));


		m_opaqueBodies.emplace_back(std::move(pTransform));
	}

}
