#include "stdafx.h"
#include "ProgramContext.h"

namespace
{
	glm::mat4 GetNormalMatrix(const glm::mat4 &modelView)
	{
		return glm::transpose(glm::inverse(modelView));
	}
}

CProgramContext::CProgramContext(size_t amountLights, size_t amountShaders)
	: m_lights(amountLights)
	, m_shaderPrograms(amountShaders)
{
}

void CProgramContext::SetModel(const glm::mat4 &value)
{
	m_model = value;
}

void CProgramContext::SetView(const glm::mat4 &value)
{
	m_view = value;
}

void CProgramContext::SetProjection(const glm::mat4 &value)
{
	m_projection = value;
}

const glm::mat4 &CProgramContext::GetModel() const
{
	return m_model;
}

const glm::mat4 &CProgramContext::GetView() const
{
	return m_view;
}

const glm::mat4 &CProgramContext::GetProjection() const
{
	return m_projection;
}

CVertexAttribute CProgramContext::GetPositionAttr() const
{
	return m_pCurrentShaderProgram->FindAttribute("vertex");
}

CVertexAttribute CProgramContext::GetNormalAttr() const
{
	return m_pCurrentShaderProgram->FindAttribute("normal");
}

CVertexAttribute CProgramContext::GetTexCoordAttr() const
{
	return m_pCurrentShaderProgram->FindAttribute("textureUV");
}

const CProgramContext::SLightSource & CProgramContext::GetLight(size_t index) const
{
	if (!IsBetween(index, size_t(0), m_lights.size() - 1))
	{
		throw std::runtime_error("Not exist light have index " + std::to_string(index));
	}
	return m_lights[index];
}

void CProgramContext::SetLight(size_t index, const SLightSource & source)
{
	if (!IsBetween(index, size_t(0), m_lights.size() - 1))
	{
		throw std::runtime_error("Not exist light have index " + std::to_string(index));
	}
	m_lights[index] = source;
}

CProgramUniform CProgramContext::FindUniform(const std::string & name) const
{
	return m_pCurrentShaderProgram->FindUniform(name);
}

void CProgramContext::Use()
{
	BindTextures();

	m_pCurrentShaderProgram->Use();

	SetTexture();
	SetView();
	SetLights();
}

void CProgramContext::SetView() const
{
	const glm::mat4 mv = m_view * m_model;
	m_pCurrentShaderProgram->FindUniform("view") = m_view;
	m_pCurrentShaderProgram->FindUniform("modelView") = mv;
	m_pCurrentShaderProgram->FindUniform("normalModelView") = GetNormalMatrix(mv);
	m_pCurrentShaderProgram->FindUniform("projection") = m_projection;
}