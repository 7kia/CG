#include "stdafx.h"
#include "Particle.h"

CParticle::CParticle() : CShape()
{
	SetOrigin(m_position);
	ChangeColor();
}

CParticle::CParticle(const glm::vec2 &position
					, float radius
					, float thiknessOutline
					, bool isNegative
					)
	: m_position(position)
	, m_radius(radius)
	, m_thikness(thiknessOutline)
{
	SetOrigin(m_position);
	ChangeColor();
}


void CParticle::Redraw() const
{
	FillCircle();
	StrokeCircle();


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
	glLineWidth(m_thikness);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = m_radius * cosf(angle);
		const float dy = m_radius * sinf(angle);
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
		const float dx = m_radius * cosf(a);
		const float dy = m_radius * sinf(a);
		glVertex2f(dx + m_position.x, dy + m_position.y);
	}
	glEnd();
}

void CParticle::DefineCenterSign()
{
	std::unique_ptr<CShape> pSign;
	if (m_isNegative)
	{
		pSign = std::make_unique<CMinus>();
	}
	else
	{
		pSign = std::make_unique<CPlus>();
	}

	pSign->SetPosition(m_position);

	m_shapeSign.reset(pSign.get());

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

void CParticle::SetRadiuse(float radius)
{
	m_radius = radius;
}

float CParticle::GetRadiuse() const
{
	return m_radius;
}

void CParticle::SetOutlineThikness(float thikness)
{
	m_thikness = thikness;
}

float CParticle::GetOutlineThikness() const
{
	return m_thikness;
}

void CParticle::SetSign(bool isNegative)
{
	m_isNegative = isNegative;
	ChangeColor();
}

bool CParticle::GetSign() const
{
	return m_isNegative;
}
