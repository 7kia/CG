#include "stdafx.h"
#include "HaveVertex.h"

CHaveThreeVertex::CHaveThreeVertex()
	: IHaveVertex()
	, m_vertex(3)
{
}

void CHaveThreeVertex::SetVertex(uint index, const Vertex & value)
{
	CheckIndex(index);
	m_vertex[index] = value;
}


Vertex CHaveThreeVertex::GetVertex(uint index) const
{
	CheckIndex(index);
	return m_vertex[index];
}

Vertex * CHaveThreeVertex::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return &m_vertex[index];
}


std::vector<Vertex> CHaveThreeVertex::GetVertexes() const
{
	std::vector<Vertex> result;
	for (size_t index = 0; index < 3; ++index)
	{
		result[index] = m_vertex[index];
	}
	return result;
}


void CHaveThreeVertex::CheckIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_vertex.size())))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}

CHaveReferenceVertex::CHaveReferenceVertex(size_t amountVertex)
	: IHaveVertex()
	, m_pVertex(amountVertex)

{
}

void CHaveReferenceVertex::SetVertex(uint index, const Vertex & value)
{
	CheckIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
 
}


Vertex CHaveReferenceVertex::GetVertex(uint index) const
{
	CheckIndex(index);
	return *m_pVertex[index][0];
}

Vertex * CHaveReferenceVertex::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return m_pVertex[index][0];
}


std::vector<Vertex> CHaveReferenceVertex::GetVertexes() const
{
	std::vector<Vertex> result;
	for (size_t index = 0; index < 3; ++index)
	{
		result[index] = *m_pVertex[index][0];
	}
	return result;
}


void CHaveReferenceVertex::CheckIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_pVertex.size())))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}

void CHaveReferenceVertex::AddReferenceVertex(uint index, Vertex * value)
{
	CheckIndex(index);

	m_pVertex[index].push_back(value);
}
