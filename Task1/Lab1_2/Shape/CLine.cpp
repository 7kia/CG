#include "stdafx.h"
#include "CLine.h"

CLine::CLine() : CShape()
{
}

CLine::CLine(const glm::vec2 &firstPoint
			, const glm::vec2 &secondPoint
			, const glm::vec3 &color
			, float thikness)
	: m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
	// TODO : m_outlineColor - not static, error
{
	(void)thikness;

	m_outlineColor = color;
}

void CLine::Redraw() const
{
	glBegin(GL_LINE_STRIP);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);

	glVertex2f(m_firstPoint.x , m_firstPoint.y);
	glVertex2f(m_secondPoint.x, m_secondPoint.y);
	
	glEnd();
}

bool CLine::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	(void)point;
	return false;
}

void CLine::SetFirstPoint(const glm::vec2 & firstPoint)
{
	m_firstPoint = firstPoint;
}

glm::vec2 CLine::GetFirstPoint() const
{
	return m_firstPoint;
}

void CLine::SetSecondPoint(const glm::vec2 & secondPoint)
{
	m_secondPoint = secondPoint;
}

glm::vec2 CLine::GetSecondPoint() const
{
	return m_secondPoint;
}

void CLine::SetThikness(float thikness)
{
	m_thikness = thikness;
}

float CLine::GetThikness() const
{
	return m_thikness;
}
