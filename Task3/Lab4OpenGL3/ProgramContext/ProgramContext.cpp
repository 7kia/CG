#include "stdafx.h"
#include "ProgramContext.h"

namespace
{
	glm::mat4 GetNormalMatrix(const glm::mat4 &modelView)
	{
		return glm::transpose(glm::inverse(modelView));
	}
}

CProgramContext::CProgramContext()
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
	return m_shaderProgram.FindAttribute("vertex");
}

CVertexAttribute CProgramContext::GetNormalAttr() const
{
	return m_shaderProgram.FindAttribute("normal");
}

CVertexAttribute CProgramContext::GetTexCoordAttr() const
{
	return m_shaderProgram.FindAttribute("textureUV");
}

void CProgramContext::SetView() const
{
	const glm::mat4 mv = m_view * m_model;
	m_shaderProgram.FindUniform("view") = m_view;
	m_shaderProgram.FindUniform("modelView") = mv;
	m_shaderProgram.FindUniform("normalModelView") = GetNormalMatrix(mv);
	m_shaderProgram.FindUniform("projection") = m_projection;


}
