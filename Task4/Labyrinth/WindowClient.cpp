#include "stdafx.h"
#include "WindowClient.h"

namespace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };

	const char VERTEX_SHADER[] = R"***(
varying vec3 n;
varying vec3 v;

void main(void)
{
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
    n = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = ftransform();
}
)***";

const char FRAGMENT_SHADER_PHONG[] = R"***(
varying vec3 n;
varying vec3 v;

void main(void)
{
    vec4 result = vec4(0.0);
    for (int li = 0; li < gl_MaxLights; ++li)
    {
        vec3 delta = gl_LightSource[li].position.w * v;
        vec3 lightDirection = normalize(gl_LightSource[li].position.xyz - delta);
        vec3 viewDirection = normalize(-v);
        vec3 reflectDirection = normalize(-reflect(lightDirection, n));

        vec4 Iamb = gl_FrontLightProduct[li].ambient;

        float diffuseAngle = max(dot(n, lightDirection), 0.0);
        vec4 Idiff = gl_FrontLightProduct[li].diffuse * diffuseAngle;
        Idiff = clamp(Idiff, 0.0, 1.0);

        float specularAngle = max(dot(reflectDirection, viewDirection), 0.0);
        vec4 Ispec = gl_FrontLightProduct[li].specular
                    * pow(specularAngle, gl_FrontMaterial.shininess / 4.0);
        Ispec = clamp(Ispec, 0.0, 1.0);

        result += Iamb + Idiff + Ispec;
    }

    gl_FragColor = gl_FrontLightModelProduct.sceneColor + result;
}
)***";

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
}

CWindowClient::CWindowClient(CWindow &window)
    : CAbstractWindowClient(window)
{
    const glm::vec3 SUNLIGHT_DIRECTION = {-1.f, 0.2f, 0.7f};
    const glm::vec4 WHITE_RGBA = {1, 1, 1, 1};
    const glm::vec4 DARK_BLUE_RGBA = {0.2f, 0.2f, 0.6f, 1.f};
    const float AMBIENT_SCALE = 0.2f;

    window.SetBackgroundColor(BLACK);
    SetupOpenGLState();

    m_programPhong.CompileShader(VERTEX_SHADER, ShaderType::Vertex);
    m_programPhong.CompileShader(FRAGMENT_SHADER_PHONG, ShaderType::Fragment);
    m_programPhong.Link();

	m_world.CreateScene();

}

void CWindowClient::OnWindowInit(const glm::ivec2 & size)
{
	(void)size;
	SetupOpenGLState();

}

void CWindowClient::OnUpdateWindow(float deltaSeconds)
{
    SetupView(GetWindow().GetWindowSize());


    // Активной будет первая программа из очереди.
	m_programPhong.Use();
	m_world.Update(deltaSeconds);
	m_world.Draw();
}

void CWindowClient::OnKeyDown(const SDL_KeyboardEvent &event)
{
	m_world.OnKeyDown(event);
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent &event)
{
	m_world.OnKeyUp(event);
}

void CWindowClient::SetupView(const glm::ivec2 &size)
{
    glViewport(0, 0, size.x, size.y);

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
