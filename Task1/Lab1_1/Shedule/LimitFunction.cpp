#include "stdafx.h"
#include "LimitFunction.h"

CLimitFunction::CLimitFunction() : CFunctionGraph()
{
}

CLimitFunction::CLimitFunction(glm::vec2 origin
								, float start
								, float end
								, const glm::vec3 & outlineColor)
	: CFunctionGraph(origin
						, start
						, end
						, outlineColor)
{
}


void CLimitFunction::Redraw() const
{
	glBegin(GL_LINE_STRIP);

	glColor3f(m_outlineColor.x, m_outlineColor.y, m_outlineColor.z);
	float step = (m_end - m_start) / AMOUNT_POINTS;
	for (float x = m_start; x <= m_end; x += step)
	{
		glVertex2f(m_origin.x + (x * SCALE_FACTOR), m_origin.y + (GetValueFunction(x) * SCALE_FACTOR));
	}

	glEnd();
}


bool CLimitFunction::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

float CLimitFunction::GetValueFunction(float x) const
{
	float numerator = sin(x);
	float denumerator = x;

	if (denumerator == 0.f)
	{
		numerator = sin(x - EPSILON);
		denumerator = x - EPSILON;
	}

	return -numerator / denumerator;// - because y-axis derected down, but up
}