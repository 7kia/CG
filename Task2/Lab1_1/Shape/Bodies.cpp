#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

CSphereQuadric::CSphereQuadric()
    : m_quadric(gluNewQuadric())
    , m_color({1, 1, 1})
{
}

CSphereQuadric::~CSphereQuadric()
{
    gluDeleteQuadric(m_quadric);
}

void CSphereQuadric::Draw() const
{
    const double radius = 1;
    const int slices = 20;
    const int stacks = 20;
    glColor3fv(glm::value_ptr(m_color));
    gluSphere(m_quadric, radius, slices, stacks);
}

void CSphereQuadric::SetColor(const glm::vec3 &color)
{
    m_color = color;
}

CConoidQuadric::CConoidQuadric()
    : m_quadric(gluNewQuadric())
    , m_color({1, 1, 1})
{
}

CConoidQuadric::~CConoidQuadric()
{
    gluDeleteQuadric(m_quadric);
}

// Рисует усечённый конус высотой 2,
// с радиусом основания 1 и радиусом верхнего торца m_topRadius.
void CConoidQuadric::Draw() const
{
    const double baseRadius = 1;
    const double height = 2;
    const int slices = 20;
    const int stacks = 1;
    glColor3fv(glm::value_ptr(m_color));
    glPushMatrix();
    glTranslatef(0, 0, -1);
    gluCylinder(m_quadric, baseRadius, m_topRadius, height, slices, stacks);
    glFrontFace(GL_CW);
    gluDisk(m_quadric, 0, baseRadius, slices, stacks);
    glFrontFace(GL_CCW);
    glTranslatef(0, 0, 2);
    gluDisk(m_quadric, 0, baseRadius, slices, stacks);
    glPopMatrix();
}

void CConoidQuadric::SetTopRadius(double value)
{
    m_topRadius = glm::clamp(value, 0.0, 1.0);
}

void CConoidQuadric::SetColor(const glm::vec3 &color)
{
    m_color = color;
}
