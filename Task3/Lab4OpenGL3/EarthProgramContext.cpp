#include "stdafx.h"
#include "EarthProgramContext.h"

namespace
{
	static const size_t AMOUNT_LIGHT_TO_EARTH_CONTEXT = 1;
}

CEarthProgramContext::CEarthProgramContext()
	: CProgramContext(AMOUNT_LIGHT_TO_EARTH_CONTEXT)
{
    CTexture2DLoader loader;

    m_pEarthTexture = loader.Load("res\\img\\earth_colormap.jpg");
    m_pCloudTexture = loader.Load("res\\img\\earth_clouds.jpg");
    m_pNightTexture = loader.Load("res\\img\\earth_at_night.jpg");

    const auto vertShader = CFilesystemUtils::LoadFileAsString("res\\fourthTaskVertexShader.vert");
    const auto fragShader = CFilesystemUtils::LoadFileAsString("res\\cloud_earth_robust.frag");
    m_shaderProgram.CompileShader(vertShader, ShaderType::Vertex);
    m_shaderProgram.CompileShader(fragShader, ShaderType::Fragment);
    m_shaderProgram.Link();
}

void CEarthProgramContext::BindTextures()
{
	// переключаемся на текстурный слот #2
	glActiveTexture(GL_TEXTURE2);
	m_pNightTexture->Bind();
	// переключаемся на текстурный слот #1
	glActiveTexture(GL_TEXTURE1);
	m_pCloudTexture->Bind();
	// переключаемся обратно на текстурный слот #0
	// перед началом рендеринга активным будет именно этот слот.
	glActiveTexture(GL_TEXTURE0);
	m_pEarthTexture->Bind();
}

void CEarthProgramContext::SetTexture()
{
	m_shaderProgram.FindUniform("colormap") = 0; // GL_TEXTURE0
	m_shaderProgram.FindUniform("surfaceDataMap") = 1; // GL_TEXTURE1
	m_shaderProgram.FindUniform("nightColormap") = 2; // GL_TEXTURE2

}

void CEarthProgramContext::SetLights()
{
	m_shaderProgram.FindUniform("light0.position") = m_lights[0].position;
	m_shaderProgram.FindUniform("light0.diffuse") = m_lights[0].diffuse;
	m_shaderProgram.FindUniform("light0.specular") = m_lights[0].specular;
}
