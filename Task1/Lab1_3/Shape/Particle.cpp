#include "stdafx.h"
#include "Particle.h"



CParticle::CParticle() : CShape()
{
}

CParticle::CParticle(const glm::vec2 &position, bool isNegative)
{
	SetPosition(position);
	SetOrigin(m_origin);
}


void CParticle::Redraw() const
{
	FillCircle();
	StrokeCircle();
}

// Рисуем контур эллипса
void CParticle::StrokeCircle() const
{
	const float step = float(2 * M_PI / AMOUNT_POINTS);

	glColor3f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b);
	glLineWidth(DEFAULT_PARTICLE::THIKNESS);

	const glm::vec2 absolutePosition = GetCenterPosition(m_origin);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = DEFAULT_PARTICLE::RADIUSE * cosf(angle);
		const float dy = DEFAULT_PARTICLE::RADIUSE * sinf(angle);
		glVertex2f(dx + absolutePosition.x, dy + absolutePosition.y);
	}
	glEnd();
}

// Рисуем закрашенный эллипс
void CParticle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glColor3f(INNER_COLOR.r, INNER_COLOR.g, INNER_COLOR.b);
	const glm::vec2 absolutePosition = GetCenterPosition(m_origin);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(absolutePosition.x, absolutePosition.y);
    for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = DEFAULT_PARTICLE::RADIUSE * cosf(a);
		const float dy = DEFAULT_PARTICLE::RADIUSE * sinf(a);
		glVertex2f(dx + absolutePosition.x, dy + absolutePosition.y);
	}
	glEnd();
}

bool CParticle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	glm::vec2 resultShift = GetCenterPosition(m_origin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_PARTICLE::RADIUSE);
}