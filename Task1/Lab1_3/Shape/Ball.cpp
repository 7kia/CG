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
	m_body = world->CreateBody(&m_defBody);
	m_defBody.type = b2_dynamicBody;

	CreateBody();
}

void CCircle::CreateBody()
{
	// Define the ground box shape.
	b2PolygonShape circleShape;

	// TODO 
	b2Vec2 points[AMOUNT_POINTS];
	const float step = float(2 * M_PI / 8);

	int index = 0;
	for (float angle = 0.f; angle <= float(2 * M_PI); angle += step, index++)
	{
		float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
		const float dx = m_radius * cosf(a);
		const float dy = m_radius * sinf(a);
		points[index].Set(dx, dy);
	}

	// The extents are the half-widths of the box.
	circleShape.Set(points, 8);//SetAsBox(50.0f, 10.0f);

										   // Add the ground fixture to the ground body.

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	m_body->CreateFixture(&fixtureDef);
}

bool CCircle::HitTest(const glm::vec2 & point) const
{
	glm::vec2 resultShift = GetCenterPosition(m_referenceSystemOrigin) - point;

	float distance = glm::length(resultShift);
	return (distance < DEFAULT_BALL::RADIUSE);
}

void CCircle::SetRadius(float radius)
{
	m_radius = radius;
}

float CCircle::GetRadius() const
{
	return m_radius;
}
