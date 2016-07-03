#include "stdafx.h"
#include "Ball.h"



CBall::CBall() : CStaticShape()
{
}

CBall::CBall(const glm::vec2 &position)
{
	SetPosition(position);
	SetOrigin(m_origin);
}


void CBall::Redraw() const
{
	FillCircle();
	StrokeCircle();
}

// ������ ������ �������
void CBall::StrokeCircle() const
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

// ������ ����������� ������
void CBall::FillCircle() const
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

bool CBall::HitTest(const glm::vec2 & point) const
{
	glm::vec2 resultShift = GetCenterPosition(m_origin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_PARTICLE::RADIUSE);
}