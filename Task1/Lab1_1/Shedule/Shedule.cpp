#include "stdafx.h"
#include "Shedule.h"

CShedule::CShedule()
{
}

CShedule::~CShedule()
{
}

void CShedule::Redraw() const
{
	for (auto & graph : m_functionsGraphs)
	{
		graph->Redraw();
	}
}

bool CShedule::HitTest(const glm::vec2 & point) const// TODO : rewrite if need
{
	return false;
}

void CShedule::AddFunctionsGraphs(std::shared_ptr<CShape> graph)
{
	m_functionsGraphs.push_back(graph);
}
