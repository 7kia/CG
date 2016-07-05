#include "stdafx.h"
#include "Ball.h"



CCircle::CCircle(b2World * world) : CDynamicBody()
{
	AddInWorld(world);
}

CCircle::CCircle(float radius, const glm::vec2 &position, b2World * world)
	: CDynamicBody()
	, m_radius(radius)

{
	AddInWorld(world);

	SetPosition(position);
	SetReferenceSystemOrigin(m_referenceSystemOrigin);
}

void CCircle::Redraw() const
{
	FillCircle();
	StrokeCircle();
}

// Рисуем контур эллипса
void CCircle::StrokeCircle() const
{
	const float step = float(2 * M_PI / AMOUNT_POINTS);


	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	//
	transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));
	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));

	glColor3f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b);
	glLineWidth(DEFAULT_BALL::THIKNESS);

	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		const float dx = m_radius * cosf(angle);
		const float dy = m_radius * sinf(angle);
		glVertex2f(dx, dy);
	}
	glEnd();

	glPopMatrix();
}

// Рисуем закрашенный эллипс
void CCircle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	//
	transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));
	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));


	glColor3f(INNER_COLOR.r, INNER_COLOR.g, INNER_COLOR.b);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);

    for (float angle = 0; angle <= float(2 * M_PI); angle += step)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = m_radius * cosf(a);
		const float dy = m_radius * sinf(a);
		glVertex2f(dx, dy);
	}
	glEnd();

	glPopMatrix();
}

void CCircle::AddInWorld(b2World * world)
{
	m_defBody.type = b2_dynamicBody;

	m_body = world->CreateBody(&m_defBody);

	CreateBody();
}

void CCircle::CreateBody()
{

	b2CircleShape circle;
	circle.m_radius = m_radius / SCALE;

	m_body->CreateFixture(&circle, 2);
}

bool CCircle::HitTest(const glm::vec2 & point) const
{
	glm::vec2 resultShift = GetCenterPosition(m_referenceSystemOrigin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_BALL::RADIUSE);
}

void CCircle::SetPosition(const glm::vec2 & position)
{
	m_defBody.position.Set(ConvertToBoxCoordinates(position.x), ConvertToBoxCoordinates(position.y));
}

void CCircle::SetPosition(float x, float y)
{
	m_defBody.position.Set(ConvertToBoxCoordinates(x), ConvertToBoxCoordinates(y));
}

glm::vec2 CCircle::GetPosition()
{
	return glm::vec2(ConvertToNormalCoordinates(m_defBody.position.x) , ConvertToNormalCoordinates(m_defBody.position.y));
}

void CCircle::SetRadius(float radius)
{
	m_radius = radius;
}

float CCircle::GetRadius() const
{
	return m_radius;
}
