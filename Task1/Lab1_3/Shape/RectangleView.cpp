#include "stdafx.h"
#include "RectangleView.h"

CRectangleView::CRectangleView()
	: CShape()
	, CRectangle()
{
}

CRectangleView::CRectangleView(SSize size, const glm::vec2 & position)
	: CShape()
	, CRectangle(size)
{
	SetPosition(position);
}

void CRectangleView::Redraw() const
{

	glm::vec3 offset = { GetCenterPosition().x, GetCenterPosition().y, 0.f };
	glm::vec3 shapeOrigin = { GetOrigin().x, GetOrigin().y, 0.f };

	glm::mat4 transform = glm::translate(glm::mat4(), offset + shapeOrigin);
	//
	transform = glm::rotate(transform, GetRotation(), glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, -shapeOrigin);
	// Сохраняем старую матрицу в стек матриц драйвера

	glPushMatrix();

	glLoadMatrixf(glm::value_ptr(transform));
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(0.f, 0.f);
	// first triangle
	glVertex2f(0.f, m_height);
	glVertex2f(m_width, m_height);
	// second triangle
	glVertex2f(m_width, 0.f);
	glVertex2f(m_width, m_height);

	glEnd();
	glPopMatrix();


}

bool CRectangleView::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}