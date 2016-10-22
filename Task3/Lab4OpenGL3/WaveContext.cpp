#include "stdafx.h"
#include "WaveContext.h"

namespace
{
	static const size_t AMOUNT_LIGHT_TO_WAVE_CONTEXT = 1;
}


CWaveProgramContext::CWaveProgramContext()
	: CProgramContext(AMOUNT_LIGHT_TO_WAVE_CONTEXT)
{
	CTexture2DLoader loader;

	m_pWaveTexture = loader.Load("res\\img\\Water1.jpg");

	const auto vertShader = CFilesystemUtils::LoadFileAsString("res\\fourthTaskVertexShader.vert");
	const auto fragShader = CFilesystemUtils::LoadFileAsString("res\\wave.frag");
	m_shaderProgram.CompileShader(vertShader, ShaderType::Vertex);
	m_shaderProgram.CompileShader(fragShader, ShaderType::Fragment);
	m_shaderProgram.Link();
}

void CWaveProgramContext::BindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	m_pWaveTexture->Bind();
}

void CWaveProgramContext::SetTexture()
{
	m_shaderProgram.FindUniform("waveTexture") = 0; // GL_TEXTURE0
}

void CWaveProgramContext::SetLights()
{
	m_shaderProgram.FindUniform("light0.position") = m_lights[0].position;
	m_shaderProgram.FindUniform("light0.diffuse") = m_lights[0].diffuse;
	m_shaderProgram.FindUniform("light0.specular") = m_lights[0].specular;
}
