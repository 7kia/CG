#pragma once

#include "libchapter3.h"

class CProgramContext
{
public:
	CProgramContext(size_t amountLights);// TODO : see need it

	struct SLightSource
	{
		glm::vec4 position;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};
//////////////////////////////////////////////////////////////////////
// Methods
public:

	void								SetModel(const glm::mat4 &value);
	void								SetView(const glm::mat4 &value);
	void								SetProjection(const glm::mat4 &value);

	const glm::mat4 &					GetModel()const;
	const glm::mat4 &					GetView()const;
	const glm::mat4	&					GetProjection()const;


	CVertexAttribute					GetPositionAttr()const;
	CVertexAttribute					GetNormalAttr()const;
	CVertexAttribute					GetTexCoordAttr()const;

	const SLightSource &				GetLight(size_t index)const;
	void								SetLight(size_t index, const SLightSource &source);


	void								Use();
protected:
	void								SetView() const;
	virtual void						BindTextures() = 0;
	virtual void						SetTexture() = 0;
	virtual void						SetLights() = 0;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	glm::mat4							m_model;
	glm::mat4							m_view;
	glm::mat4							m_projection;
	glm::mat4							m_normalModelView;

	CShaderProgram						m_shaderProgram;

	std::vector<SLightSource>			m_lights;// TODO : transfer to other place

};