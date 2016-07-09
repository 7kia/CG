#include "stdafx.h"
#include "Ball.h"



CCircle::CCircle(b2World * world) 
	: CDynamicBody(world)
{
}

CCircle::CCircle(float radius, const glm::vec2 &position, b2World * world)
	: CDynamicBody(world)
	, m_radius(radius)

{
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

	// TODO : dudpicate code
	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	//
	transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	// Сохраняем старую матрицу в стек матриц драйвера

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
void CCircle::FillCircle() const
{
	const float step = float(2 * M_PI) / AMOUNT_POINTS;

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	//
	transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	// Сохраняем старую матрицу в стек матриц драйвера

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

void CCircle::AddToWorld(b2World * world)
{	
	CheckParametres();
	CStaticShape::AddToWorld(world);
	AddCircleToBody(m_body, m_radius);
}

void CCircle::AddCircleToBody(b2Body *body, float radius)
{
	b2CircleShape circleShape;
	circleShape.m_radius = ConvertToBoxCoordinates(radius);

	b2FixtureDef circle;
	circle.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	circle.density = 1.0f;

	// Override the default friction.
	circle.friction = 0.3f;

	circle.restitution = 1.f;

	// Add the shape to the body.
	body->CreateFixture(&circle);// TODO : magic value

	//m_body->CreateFixture(&circle, 2);
}

void CCircle::CheckParametres()
{
	CStaticShape::CheckParametres();
	CDynamicBody::CheckParametres();

	/*
	if (m_radius == NONE_VALUE::FLOAT)
	{
		throw std::runtime_error("Not define circle radius!!!")
	}
	*/
	
}

bool CCircle::HitTest(const glm::vec2 & point) const
{
	glm::vec2 resultShift = GetCenterPosition(m_referenceSystemOrigin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_BALL::RADIUSE);
}

void CCircle::SetRadius(float radius)
{
	m_radius = ConvertToBoxCoordinates(radius);
}

float CCircle::GetRadius() const
{
	return ConvertToNormalCoordinates(m_radius);
}
