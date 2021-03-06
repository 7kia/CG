#include "stdafx.h"
#include "Particle.h"


CParticle::CParticle() : CShape()
{
	SetSign(false);
}

CParticle::CParticle(const glm::vec2 &position, bool isNegative)
{
	SetPosition(position);
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

// ������ ������ �������
void CParticle::StrokeCircle() const
{
	const float step = float(2 * M_PI / AMOUNT_POINTS);

	glColor3f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b);
	glLineWidth(DEFAULT_PARTICLE::THIKNESS);

	const glm::vec2 absolutePosition = GetCenterPosition();

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = DEFAULT_PARTICLE::RADIUS * cosf(angle);
		const float dy = DEFAULT_PARTICLE::RADIUS * sinf(angle);
		glVertex2f(dx + absolutePosition.x, dy + absolutePosition.y);
	}
	glEnd();
}

// ������ ����������� ������
void CParticle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glColor3f(INSIDE_COLOR.r, INSIDE_COLOR.g, INSIDE_COLOR.b);
	const glm::vec2 absolutePosition = GetCenterPosition();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(absolutePosition.x, absolutePosition.y);
    for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = DEFAULT_PARTICLE::RADIUS * cosf(a);
		const float dy = DEFAULT_PARTICLE::RADIUS * sinf(a);
		glVertex2f(dx + absolutePosition.x, dy + absolutePosition.y);
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
	m_shapeSign->SetOrigin(GetOrigin());

}


bool CParticle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	glm::vec2 resultShift = GetCenterPosition() - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_PARTICLE::RADIUS);
}

void CParticle::SetPosition(const glm::vec2 & position)
{
	CHavePosition::SetPosition(position);

	m_shapeSign->SetPosition(position);
}

void CParticle::SetPosition(float x, float y)
{
	CHavePosition::SetPosition(x, y);

	m_shapeSign->SetPosition(x, y);
}

void CParticle::SetOrigin(const glm::vec2 & origin)
{
	CShape::SetOrigin(origin);

	m_shapeSign->SetOrigin(origin);
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

float CParticle::GetMass() const
{
	return m_isNegative ? ELECTRON_MASS : PROTON_MASS;
}
