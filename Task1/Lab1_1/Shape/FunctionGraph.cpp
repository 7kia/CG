#include "stdafx.h"
#include "FunctionGraph.h"

CFunctionGraph::CFunctionGraph()
{
}

CFunctionGraph::CFunctionGraph(glm::vec2 origin
								, float start
								, float end
								, const glm::vec3 & outlineColor)
	: m_origin(origin)
	, m_start(start)
	, m_end(end)
{
	SetOutlineColor(outlineColor);
}

CFunctionGraph::~CFunctionGraph()
{
}

void CFunctionGraph::Redraw() const
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

bool CFunctionGraph::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

void CFunctionGraph::SetOrigin(const glm::vec2 & origin)
{
	m_origin = origin;
}

glm::vec2 CFunctionGraph::GetOrigin() const
{
	return m_origin;
}

void CFunctionGraph::SetStart(float start)
{
	m_start = start;
}

float CFunctionGraph::GetStart() const
{
	return m_start;
}

void CFunctionGraph::SetEnd(float end)
{
	m_end = end;
}

float CFunctionGraph::GetEnd() const
{
	return m_end;
}

float CFunctionGraph::GetValueFunction(float x) const
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
