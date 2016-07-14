#include "stdafx.h"
#include "Minus.h"

CMinus::CMinus() 
	: CShape()
	, boost::noncopyable()
{
	SetOutlineColor(NEGATIVE_COLOR);
}

CMinus::CMinus(const glm::vec2 & position)
	: CShape()
	, boost::noncopyable()
{
	SetPosition(position);
	SetOrigin(position);

	SetOutlineColor(NEGATIVE_COLOR);
}

void CMinus::Redraw() const
{
	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	const glm::vec2 absolutePosition = GetCenterPosition();

	glVertex2f(absolutePosition.x - HEIGHT_SIGN / 2.f, absolutePosition.y - WIDTH_SIGN / 2.f);
	// first triangle
	glVertex2f(absolutePosition.x - HEIGHT_SIGN / 2.f, absolutePosition.y + WIDTH_SIGN / 2.f);
	glVertex2f(absolutePosition.x + HEIGHT_SIGN / 2.f, absolutePosition.y + WIDTH_SIGN / 2.f);
	// second triangle
	glVertex2f(absolutePosition.x + HEIGHT_SIGN / 2.f, absolutePosition.y - WIDTH_SIGN / 2.f);
	glVertex2f(absolutePosition.x + HEIGHT_SIGN / 2.f, absolutePosition.y + WIDTH_SIGN / 2.f);

	glEnd();

}

bool CMinus::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}