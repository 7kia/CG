#include "stdafx.h"
#include "Rectangle.h"

template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

CRectangle::CRectangle()
{
}

CRectangle::CRectangle(const glm::vec2 & leftTopPoint
						, float width
						, float height
						, float rotate
						, const glm::vec3 & outlineColor)
{
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

	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	//
	transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));
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
