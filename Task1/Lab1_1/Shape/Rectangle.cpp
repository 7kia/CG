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
						, const glm::vec3 & outlineColor)
{
	m_rect.w = width;
	m_rect.h = height;
	m_rect.x = leftTopPoint.x;
	m_rect.y = leftTopPoint.y;

	SetOutlineColor(outlineColor);// TODO : error if in list initialization
	SetWidth(width);
	SetHeight(height);
}

CRectangle::~CRectangle()
{
}

void CRectangle::Redraw() const
{
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(m_rect.x, m_rect.y);
	// first triangle
	glVertex2f(m_rect.x, m_rect.y + m_rect.h);
	glVertex2f(m_rect.x + m_rect.w, m_rect.y + m_rect.h);
	// second triangle
	glVertex2f(m_rect.x + m_rect.w, m_rect.y);
	glVertex2f(m_rect.x + m_rect.w, m_rect.y + m_rect.h);

	glEnd();
}

bool CRectangle::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

void CRectangle::SetLeftTopPoint(const glm::vec2 & leftTopPoint)
{
	m_rect.x = leftTopPoint.x;
	m_rect.y = leftTopPoint.y;
}

void CRectangle::SetLeftTopPoint(float x, float y)
{
	m_rect.x = x;
	m_rect.y = y;
}

glm::vec2 CRectangle::GetLeftTopPoint() const
{
	return glm::vec2(m_rect.x, m_rect.y);
}

void CRectangle::SetWidth(float width)
{
	if (width < 0)
	{
		m_rect.w = 0;
	}
	else
	{
		m_rect.w = width;
	}
}

float CRectangle::GetWidth() const
{
	return m_rect.w;
}

void CRectangle::SetHeight(float height)
{
	if (height < 0)
	{
		m_rect.h = 0;
	}
	else
	{
		m_rect.h = height;
	}
}

float CRectangle::GetHeight() const
{
	return m_rect.h;
}