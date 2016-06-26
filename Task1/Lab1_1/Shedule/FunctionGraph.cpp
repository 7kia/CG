#include "stdafx.h"
#include "FunctionGraph.h"

CFunctionGraph::CFunctionGraph(glm::vec2 origin
								, float start
								, float end
								, const glm::vec3 & outlineColor)
	: m_start(start)
	, m_end(end)
{
	SetOrigin(origin);
	SetOutlineColor(outlineColor);
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