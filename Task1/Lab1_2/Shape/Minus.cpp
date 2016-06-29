#include "stdafx.h"
#include "Minus.h"

CMinus::CMinus() 
	: CShape()
	, CHavePosition()
	, boost::noncopyable()
{
}

CMinus::CMinus(const glm::vec2 & position)
	: CShape()
	, CHavePosition()
	, boost::noncopyable()
{
	SetPosition(position);
	SetOrigin(position);
}

CMinus::~CMinus()
{
}


void CMinus::Redraw() const
{
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(m_position.x - WIDTH_SIGN / 2.f, m_position.y - HEIGHT_SIGN / 2.f);
	// first triangle
	glVertex2f(m_position.x - WIDTH_SIGN / 2.f, m_position.y + HEIGHT_SIGN / 2.f);
	glVertex2f(m_position.x + WIDTH_SIGN / 2.f, m_position.y + HEIGHT_SIGN / 2.f);
	// second triangle
	glVertex2f(m_position.x + WIDTH_SIGN / 2.f, m_position.y - HEIGHT_SIGN / 2.f);
	glVertex2f(m_position.x + WIDTH_SIGN / 2.f, m_position.y + HEIGHT_SIGN / 2.f);

	glEnd();

}

bool CMinus::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}