#include "stdafx.h"
#include "HaveVertex.h"

CHaveVertex::CHaveVertex(size_t amountVertex)
	: IHaveVertex()
	, m_amountVertex(amountVertex)
	, m_vertex(amountVertex)
{
}

void CHaveVertex::SetVertex(int index, const Vertex & value)
{
	CheckIndex(index);
	m_vertex[index] = value;
}


Vertex CHaveVertex::GetVertex(int index) const
{
	CheckIndex(index);
	return m_vertex[index];
}


std::vector<Vertex> CHaveVertex::GetVertexes() const
{
	std::vector<Vertex> result;
	for (size_t index = 0; index < 3; ++index)
	{
		result[index] = m_vertex[index];
	}
	return result;
}


void CHaveVertex::CheckIndex(int index) const
{
	if (!IsBetween(index, 0, int(m_amountVertex)))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}