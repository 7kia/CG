#include "stdafx.h"
#include "Lights.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace
{
}

CAbstractLightSource::CAbstractLightSource(unsigned index)
    : ILightSource()
	, IDrawable()
	, CMaterialCharactiristics()
	, m_index(index)
	, m_visual(20, 20)
{
}


void CAbstractLightSource::SetupImpl() const
{
    // Включаем источник света с заданным индексом.
    // Источник действует только когда включен режим GL_LIGHTING!
    glEnable(GLenum(m_index));
    glLightfv(m_index, GL_AMBIENT, glm::value_ptr(m_ambient));
    glLightfv(m_index, GL_DIFFUSE, glm::value_ptr(m_diffuse));
    glLightfv(m_index, GL_SPECULAR, glm::value_ptr(m_specular));
}

unsigned CAbstractLightSource::GetIndex() const
{
    return m_index;
}

void CAbstractLightSource::Draw() const
{
	m_visual.Draw();
}

CDirectedLightSource::CDirectedLightSource(unsigned index)
    : CAbstractLightSource(index)
	, CHaveDirection()
{
}


void CDirectedLightSource::Setup() const
{
    SetupImpl();
    // Если GL_POSITION установить как (x, y, z, 0), т.е. как вектор
    // в однородных координатах, источник света будет направленным.
    glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(m_direction));
}

CPositionLightSource::CPositionLightSource(unsigned index)
    : CAbstractLightSource(index)
    , CHave3DPosition()
{
	m_position = { 0.f, 0.f, 0.f, 1.f };
}

void CPositionLightSource::Setup() const
{
    SetupImpl();
    // Если GL_POSITION установить как (x, y, z, 1), т.е. как точку
    // в однородных координатах, источник света будет точечным.
    glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(m_position));
}

void CPositionLightSource::Disable() const
{
	glDisable(GLenum(m_index));
}

void CPositionLightSource::Draw() const
{
	glPushMatrix();

	const glm::vec3 position3D = { m_position.x, m_position.y, m_position.z };
	auto transform = glm::translate(glm::mat4(), position3D);
	glMultMatrixf(glm::value_ptr(transform));

	CAbstractLightSource::Draw();

	glPopMatrix();
}
