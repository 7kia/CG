#include "stdafx.h"
#include "Rectangle.h"
/*
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
	: m_rotation(rotate)
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
	glm::vec3 offset = { m_rect.x, m_rect.y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset );
	//
	transform = glm::rotate(transform, m_rotation, glm::vec3(0.f, 0.f, 1.f));
	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(0.f, 0.f);
	// first triangle
	glVertex2f(0.f, 0.f + m_rect.h);
	glVertex2f(0.f + m_rect.w, 0.f + m_rect.h);
	// second triangle
	glVertex2f(0.f + m_rect.w, 0.f);
	glVertex2f(0.f + m_rect.w, 0.f + m_rect.h);

	glEnd();
	glPopMatrix();

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

void CRectangle::SetRotate(float angle)
{
	m_rotation = angle;
}

float CRectangle::GetRotate() const
{
	return m_rotation;
}

*/

CRectangle::CRectangle()
	: СCompositeShape()
{
	{
		auto FirstTriangle = std::make_unique<CTriangle>();
		FirstTriangle->SetVertex(0u, glm::vec3(-1.f, 1.f, 0.f));
		FirstTriangle->SetVertex(1u, glm::vec3(1.f, 1.f, 0.f));
		FirstTriangle->SetVertex(2u, glm::vec3(-1.f, -1.f, 0.f));

		m_shapes.emplace_back(std::move(FirstTriangle));
	}
	{
		auto SecondTriangle = std::make_unique<CTriangle>();
		SecondTriangle->SetVertex(0u, glm::vec3(1.f, 1.f, 0.f));
		SecondTriangle->SetVertex(1u, glm::vec3(1.f, -1.f, 0.f));
		SecondTriangle->SetVertex(2u, glm::vec3(-1.f, -1.f, 0.f));

		m_shapes.emplace_back(std::move(SecondTriangle));
	}
}


void CRectangle::Update(float deltaTime)
{
	(void)deltaTime;
}