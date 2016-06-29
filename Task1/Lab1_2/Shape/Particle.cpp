#include "stdafx.h"
#include "Particle.h"

namespace DEFAULT_PARTICLE
{
	const float	RADIUSE = 25.f;
	const float	THIKNESS = 4.f;
}


CParticle::CParticle() : CShape()
{
	SetOrigin(m_position);
	SetSign(false);
}

CParticle::CParticle(const glm::vec2 &position, bool isNegative)
	: m_position(position)
{
	SetOrigin(m_position);
	SetSign(isNegative);
}


void CParticle::Redraw() const
{
	FillCircle();
	StrokeCircle();

	m_shapeSign->Redraw();
}

void CParticle::ChangeColor()
{
	if (m_isNegative)
	{
		SetOutlineColor(NEGATIVE_COLOR);
	}
	else
	{
		SetOutlineColor(POSITIVE_COLOR);
	}
}

// Рисуем контур эллипса
void CParticle::StrokeCircle() const
{
	const float step = float(2 * M_PI / AMOUNT_POINTS);

	glColor3f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b);
	glLineWidth(DEFAULT_PARTICLE::THIKNESS);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = DEFAULT_PARTICLE::RADIUSE * cosf(angle);
		const float dy = DEFAULT_PARTICLE::RADIUSE * sinf(angle);
		glVertex2f(dx + m_position.x, dy + m_position.y);
	}
	glEnd();
}

// Рисуем закрашенный эллипс
void CParticle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glColor3f(INSIDE_COLOR.r, INSIDE_COLOR.g, INSIDE_COLOR.b);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(m_position.x, m_position.y);
    for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = DEFAULT_PARTICLE::RADIUSE * cosf(a);
		const float dy = DEFAULT_PARTICLE::RADIUSE * sinf(a);
		glVertex2f(dx + m_position.x, dy + m_position.y);
	}
	glEnd();
}

void CParticle::DefineCenterSign()
{
	if (m_isNegative)
	{
		m_shapeSign = std::make_unique<CMinus>();
	}
	else
	{
		m_shapeSign = std::make_unique<CPlus>();
	}

	m_shapeSign->SetPosition(m_position);
}


bool CParticle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}

void CParticle::SetPosition(const glm::vec2 & position)
{
	m_position = position;
}

glm::vec2 CParticle::GetPosition() const
{
	return m_position;
}

void CParticle::SetSign(bool isNegative)
{
	m_isNegative = isNegative;
	ChangeColor();
	DefineCenterSign();
}

bool CParticle::GetSign() const
{
	return m_isNegative;
}
