#include "stdafx.h"
#include "WindowClient.h"

namespace
{
const glm::vec2 QUAD_TOPLEFT = { -200, -200 };
const glm::vec2 QUAD_SIZE = { 400, 400 };

// TODO : rewrite
std::vector<SVertexP2T2> Stroke5PointStar(const glm::vec2 & center, float outRadius, float innerRadius)
{
	const float STEP = float(M_PI * 4 / 5);

	std::vector<SVertexP2T2> result;

	float angle = float(-0.5 * M_PI);

	// Center point
	//result.push_back(SVertexP2T2(center, glm::vec2()));
	// Соединяем отрезками прямой линии точки, расположенные на окружности
	// в точках, с углами: -90, 54, 198, 342, 486 (126) градусов

	//////////////////////////////////
	// TODO : 10 triangles * 3 vertex
	glm::vec2 currentVertex;
	size_t amountVertex = 5;
	for (size_t vertexIndex = 0; vertexIndex < amountVertex; ++vertexIndex)
	{
		const float angleShift = 1.f + STEP * float(vertexIndex);
		float x;
		float y;

		x = center.x + innerRadius * cos(angle);
		y = center.y + innerRadius * sin(angle);
		//return vec2(x, y);
		currentVertex.x = x;
		currentVertex.y = y;

		///
		///
		///
		result.push_back(SVertexP2T2(currentVertex, glm::vec2()));
		angle += STEP;
	}
	//////////////////////////////////
	/*
		for (int i = 0; i < 5; ++i, angle += STEP)
	{
		float x = center.x + outRadius * cosf(angle);
		float y = center.y + outRadius * sinf(angle);
		// функция glVertex2f добавляет в текущую группу примитивов
		// точку, лежащую на плоскости z = 0
		// суффикс 2f в названии функции обозначает, что задаются 2 координаты
		// x и y типа GLfloat
		result.push_back(SVertexP2T2(glm::vec2(x, y), glm::vec2() ));

		x = center.x + innerRadius * cosf(angle + STEP / 2.f);
		y = center.y + innerRadius * sinf(angle + STEP / 2.f);

		result.push_back(SVertexP2T2(glm::vec2(x, y), glm::vec2()));

	}
	*/
	// Sort vertex
	/*
	for (int index = 3; index < amountVertex; index += 3)
	{
		if (result[index + 1].position.x < result[index + 2].position.x)
		{
			glm::vec2 buffer = result[index + 1].position;

			result[index + 1] = result[index + 2];
			result[index + 2].position = buffer;
		}

	}
	*/
	
	
	return result;
}
/////////////////////////

void SetupOpenGLState()
{
    // включаем механизмы трёхмерного мира.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
    , m_quadObj(QUAD_TOPLEFT, QUAD_SIZE)
{
    const glm::vec4 GREEN = { 0.15f, 0.4f, 0.15f, 1.f };
    GetWindow().SetBackgroundColor(GREEN);
    CheckOpenGLVersion();
    SetupOpenGLState();

    const std::string vertexShader = CFilesystemUtils::LoadFileAsString("res/copytexture.vert");
    const std::string checkersShader = CFilesystemUtils::LoadFileAsString("res/checkers.frag");
    const std::string pictureShader = CFilesystemUtils::LoadFileAsString("res/checkers-and-triangle.frag");

    m_programCheckers.CompileShader(vertexShader, ShaderType::Vertex);
    m_programCheckers.CompileShader(checkersShader, ShaderType::Fragment);
    m_programCheckers.Link();

    m_programPicture.CompileShader(vertexShader, ShaderType::Vertex);
    m_programPicture.CompileShader(pictureShader, ShaderType::Fragment);
    m_programPicture.Link();

    m_programQueue = { &m_programPicture, &m_programCheckers };

	// TODO : rewrite
	auto vertexes = Stroke5PointStar(glm::vec2(1.0f, 1.0f)
									, 2.0f
									, 1.0f);

}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    (void)deltaSeconds;
    SetupView(GetWindow().GetWindowSize());

    // Активной будет первая программа из очереди.
    m_programQueue.front()->Use();
    m_quadObj.Draw();
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
    // Передвигаем очередь программ,
    // если была нажата и отпущена клавиша "Пробел"
    if (event.keysym.sym == SDLK_SPACE)
    {
        std::rotate(m_programQueue.begin(), m_programQueue.begin() + 1, m_programQueue.end());
    }
}

void CWindowClient::CheckOpenGLVersion()
{
    // В OpenGL 2.0 шейдерные программы вошли в спецификацию API.
    if (!GLEW_VERSION_2_0)
    {
        throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
    }
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const float halfWidth = float(size.x) * 0.5f;
    const float halfHeight = float(size.y) * 0.5f;
    const glm::mat4 matrix = glm::ortho<float>(-halfWidth, halfWidth, -halfHeight, halfHeight);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
