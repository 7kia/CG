#include "stdafx.h"
#include "Particle.h"

namespace DEFAULT_PARTICLE
{
	const float	RADIUSE = 25.f;
	const float	THIKNESS = 4.f;
}


CParticle::CParticle() : CShape()
{
	SetSign(false);
}

CParticle::CParticle(const glm::vec2 &position, bool isNegative)
	: m_position(position)
{
	SetPosition(m_position);
	SetOrigin(m_origin);
	SetSign(isNegative);
}


void CParticle::Redraw() const
{
	// ������������ Model-View �������,
	// ������ ��� ����� ����������� �� ������ (x, y, 0)
	glm::vec3 offset = { m_position.x, m_position.y, 0.f };
	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	// ��������� ������ ������� � ���� ������ ��������
	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	FillCircle();
	StrokeCircle();

	m_shapeSign->Redraw();

	// ��������� ������ ������� �� ����� ������ ��������
	glPopMatrix();
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

	const glm::vec2 absolutePosition = GetAbsolutePosition(m_origin);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = DEFAULT_PARTICLE::RADIUSE * cosf(angle);
		const float dy = DEFAULT_PARTICLE::RADIUSE * sinf(angle);
		glVertex2f(dx + absolutePosition.x, dy + absolutePosition.y);
	}
	glEnd();
}

// ������ ����������� ������
void CParticle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glColor3f(INSIDE_COLOR.r, INSIDE_COLOR.g, INSIDE_COLOR.b);
	const glm::vec2 absolutePosition = GetAbsolutePosition(m_origin);

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
	m_shapeSign->SetOrigin(m_origin);

}


bool CParticle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	glm::vec2 resultShift = point - m_position;


	return (glm::length(resultShift) < DEFAULT_PARTICLE::RADIUSE);
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
