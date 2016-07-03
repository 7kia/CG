#include "stdafx.h"
#include "Plus.h"

CPlus::CPlus()
	: CMinus()
{
	SetOutlineColor(POSITIVE_COLOR);
}

CPlus::CPlus(const glm::vec2 & position)
	: CMinus()
{
	SetPosition(position);
	SetOrigin(position);

	SetOutlineColor(POSITIVE_COLOR);
}



void CPlus::Redraw() const
{
	CMinus::Redraw();

	glBegin(GL_TRIANGLE_FAN);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	const glm::vec2 absolutePosition = GetCenterPosition(m_origin);

	glVertex2f(absolutePosition.x - WIDTH_SIGN / 2.f, absolutePosition.y - HEIGHT_SIGN / 2.f);
	// first triangle
	glVertex2f(absolutePosition.x - WIDTH_SIGN / 2.f, absolutePosition.y + HEIGHT_SIGN / 2.f);
	glVertex2f(absolutePosition.x + WIDTH_SIGN / 2.f, absolutePosition.y + HEIGHT_SIGN / 2.f);
	// second triangle
	glVertex2f(absolutePosition.x + WIDTH_SIGN / 2.f, absolutePosition.y - HEIGHT_SIGN / 2.f);
	glVertex2f(absolutePosition.x + WIDTH_SIGN / 2.f, absolutePosition.y + HEIGHT_SIGN / 2.f);

	glEnd();

}

bool CPlus::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}