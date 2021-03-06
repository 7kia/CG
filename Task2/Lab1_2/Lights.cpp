#include "stdafx.h"
#include "Lights.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace
{
}

CAbstractLightSource::CAbstractLightSource(unsigned index)
    : m_index(index)
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
    , CHavePosition()
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

CPhongModelMaterial::CPhongModelMaterial()
	: CHaveEmission()
	, CHaveAmbient()
	, CHaveDiffuse()
	, CHaveSpecular()
	, CHaveShininess()
{
}

void CPhongModelMaterial::Setup() const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}