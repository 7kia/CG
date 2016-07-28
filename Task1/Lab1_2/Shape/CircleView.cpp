#include "stdafx.h"
#include "CircleView.h"

CCircleView::CCircleView()
	: CShape()
	, CCircle()
{
}

CCircleView::CCircleView(float radius, const glm::vec2 & position)
	: CShape()
	, CCircle(radius)
{
	SetPosition(position);
}

void CCircleView::Redraw() const
{
	FillCircle();
	StrokeCircle();
}

// Рисуем контур эллипса
void CCircleView::StrokeCircle() const
{
	const float step = float(2 * M_PI / AMOUNT_POINTS);

	// TODO : dudpicate code
	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };
	glm::vec3 shapeOrigin = { GetOrigin().x, GetOrigin().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	//
	//transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	glColor3f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b);
	glLineWidth(DEFAULT_BALL::THIKNESS);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = GetRadius() * cosf(angle);
		const float dy = GetRadius() * sinf(angle);
		glVertex2f(dx, dy);
	}
	glEnd();

	glPopMatrix();
}

// Рисуем закрашенный эллипс
void CCircleView::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };
	glm::vec3 shapeOrigin = { GetOrigin().x, GetOrigin().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	//
	//transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));


	glColor3f(INNER_COLOR.r, INNER_COLOR.g, INNER_COLOR.b);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);

	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = GetRadius() * cosf(a);
		const float dy = GetRadius() * sinf(a);
		glVertex2f(dx, dy);
	}
	glEnd();

	glPopMatrix();
}


bool CCircleView::HitTest(const glm::vec2 & point) const
{
	glm::vec2 resultShift = GetCenterPosition(m_referenceSystemOrigin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_BALL::RADIUSE);
}