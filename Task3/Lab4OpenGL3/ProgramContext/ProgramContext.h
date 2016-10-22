#pragma once

#include "libchapter3.h"

class CProgramContext
{
public:
	CProgramContext();// TODO : see need it
//////////////////////////////////////////////////////////////////////
// Methods
public:

	void					SetModel(const glm::mat4 &value);
	void					SetView(const glm::mat4 &value);
	void					SetProjection(const glm::mat4 &value);

	const glm::mat4 &		GetModel()const;
	const glm::mat4 &		GetView()const;
	const glm::mat4	&		GetProjection()const;


	CVertexAttribute		GetPositionAttr()const;
	CVertexAttribute		GetNormalAttr()const;
	CVertexAttribute		GetTexCoordAttr()const;

	virtual	void			Use() = 0;
protected:
	void					SetView() const;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::mat4				m_model;
	glm::mat4				m_view;
	glm::mat4				m_projection;
	glm::mat4				m_normalModelView;

	CShaderProgram			m_shaderProgram;

};