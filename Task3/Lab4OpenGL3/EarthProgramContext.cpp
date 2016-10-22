#include "stdafx.h"
#include "EarthProgramContext.h"


CEarthProgramContext::CEarthProgramContext()
	: CProgramContext()
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

void CEarthProgramContext::Use()
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

    m_shaderProgram.Use();
    m_shaderProgram.FindUniform("colormap") = 0; // GL_TEXTURE0
    m_shaderProgram.FindUniform("surfaceDataMap") = 1; // GL_TEXTURE1
    m_shaderProgram.FindUniform("nightColormap") = 2; // GL_TEXTURE2

	SetView();

    m_shaderProgram.FindUniform("light0.position") = m_light0.position;
    m_shaderProgram.FindUniform("light0.diffuse") = m_light0.diffuse;
    m_shaderProgram.FindUniform("light0.specular") = m_light0.specular;
}


const CEarthProgramContext::SLightSource &CEarthProgramContext::GetLight0() const
{
    return m_light0;
}

void CEarthProgramContext::SetLight0(const CEarthProgramContext::SLightSource &source)
{
    m_light0 = source;
}
