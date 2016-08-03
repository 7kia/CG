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
    , m_position(0, 0, 0, 1)
{
}

glm::vec3 CPositionLightSource::GetPosition() const
{
    return { m_position.x, m_position.y, m_position.z };
}

void CPositionLightSource::SetPosition(const glm::vec3 &value)
{
    m_position.x = value.x;
    m_position.y = value.y;
    m_position.z = value.z;
}

void CPositionLightSource::Setup() const
{
    SetupImpl();
    // Если GL_POSITION установить как (x, y, z, 1), т.е. как точку
    // в однородных координатах, источник света будет точечным.
    glLightfv(GetIndex(), GL_POSITION, glm::value_ptr(m_position));
}

void CPhongModelMaterial::Setup() const
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(m_emission));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(m_ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(m_diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(m_specular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
}

glm::vec4 CPhongModelMaterial::GetEmission() const
{
    return m_emission;
}

void CPhongModelMaterial::SetEmission(const glm::vec4 &emission)
{
    m_emission = emission;
}

glm::vec4 CPhongModelMaterial::GetAmbient() const
{
    return m_ambient;
}

void CPhongModelMaterial::SetAmbient(const glm::vec4 &ambient)
{
    m_ambient = ambient;
}

glm::vec4 CPhongModelMaterial::GetDiffuse() const
{
    return m_diffuse;
}

void CPhongModelMaterial::SetDiffuse(const glm::vec4 &diffuse)
{
    m_diffuse = diffuse;
}

glm::vec4 CPhongModelMaterial::GetSpecular() const
{
    return m_specular;
}

void CPhongModelMaterial::SetSpecular(const glm::vec4 &specular)
{
    m_specular = specular;
}

float CPhongModelMaterial::GetShininess() const
{
    return m_shininess;
}

void CPhongModelMaterial::SetShininess(float shininess)
{
    m_shininess = shininess;
}
