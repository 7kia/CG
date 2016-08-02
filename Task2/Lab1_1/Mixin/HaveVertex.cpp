#include "stdafx.h"
#include "HaveVertex.h"

CHaveVertex::CHaveVertex(size_t amountVertex)
	: IHaveVertex()
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

Vertex * CHaveVertex::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return &m_vertex[index];
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
	if (!IsBetween(index, 0, int(m_vertex.size())))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}

CHaveReferenceVertex::CHaveReferenceVertex(size_t amountVertex)
	: IHaveVertex()
	, m_pVertex(amountVertex)

{
}

void CHaveReferenceVertex::SetVertex(int index, const Vertex & value)
{
	CheckIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
 
}


Vertex CHaveReferenceVertex::GetVertex(int index) const
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


void CHaveReferenceVertex::CheckIndex(int index) const
{
	if (!IsBetween(index, 0, int(m_pVertex.size())))
	{
		throw std::runtime_error("Vertex have the index not exist");
	}
}

void CHaveReferenceVertex::AddReferenceVertex(int index, Vertex * value)
{
	CheckIndex(index);

	m_pVertex[index].push_back(value);
}
