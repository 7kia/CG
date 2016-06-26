#include "stdafx.h"
#include "ArchimedeanSpiral.h"

CArchimedeanSpiral::CArchimedeanSpiral() : CFunctionGraph()
{
}

CArchimedeanSpiral::CArchimedeanSpiral(glm::vec2 origin
										, float start
										, float end
										, const glm::vec3 & outlineColor)
			: CFunctionGraph(origin
				, start
				, end
				, outlineColor)
{
}


void CArchimedeanSpiral::Redraw() const
{
	glBegin(GL_LINE_STRIP);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);
	float step = (m_end - m_start) / AMOUNT_POINTS;
	for (float angle = m_start; angle <= m_end; angle += step)
	{
		glVertex2f(m_origin.x + (GetX(angle) * SCALE_FACTOR), m_origin.y + (GetValueFunction(angle) * SCALE_FACTOR));
	}

	glEnd();
}


bool CArchimedeanSpiral::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

float CArchimedeanSpiral::GetValueFunction(float angle) const
{
	return -(m_spiralStep * angle* sin(angle));// - because y-axis derected down, but up
}

float CArchimedeanSpiral::GetX(float angle) const
{
	return (m_spiralStep * abs(angle) * cos(angle));
}

// (m_spiralStep * angle * sin(angle));
// (m_spiralStep * angle * abs(cos(angle)));
