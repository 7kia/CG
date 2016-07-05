#include "stdafx.h"
#include "Rectangle.h"

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

CRectangle::CRectangle(b2World * world) 
	: CStaticShape()
{
	AddInWorld(world);

}

CRectangle::CRectangle(const glm::vec2 & leftTopPoint
						, float width
						, float height
						, float rotate
						, const glm::vec3 & outlineColor
						, b2World * world)
{
	AddInWorld(world);

	SetWidth(width);
	SetHeight(height);
	SetPosition(leftTopPoint);

	SetOutlineColor(outlineColor);
	SetWidth(width);
	SetHeight(height);

	SetRotation(rotate);
}

CRectangle::~CRectangle()
{
}

void CRectangle::Redraw() const
{

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };
	glm::vec3 shapeOrigin = { GetShapeOrigin().x, GetShapeOrigin().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	//
	transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);
	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(0.f, 0.f);
	// first triangle
	glVertex2f(0.f, m_height);
	glVertex2f(m_width,m_height);
	// second triangle
	glVertex2f(m_width, 0.f);
	glVertex2f(m_width, m_height);

	glEnd();
	glPopMatrix();


}

bool CRectangle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}

void CRectangle::SetWidth(float width)
{
	if (width < 0)
	{
		m_width = 0;
	}
	else
	{
		m_width = width;
	}
}

float CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetHeight(float height)
{
	if (height < 0)
	{
		m_height = 0;
	}
	else
	{
		m_height = height;
	}
}

float CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::AddInWorld(b2World * world)
{
	m_body = world->CreateBody(&m_defBody);
	m_defBody.type = b2_staticBody;

	CreateBody();
}

void CRectangle::CreateBody()
{
	// Define the ground box shape.
	b2PolygonShape rectangleShape;

	// The extents are the half-widths of the box.
	rectangleShape.SetAsBox(m_width / SCALE, m_height / SCALE);//SetAsBox(50.0f, 10.0f);

							   // Add the ground fixture to the ground body.
	m_body->CreateFixture(&rectangleShape, 2.f);
}