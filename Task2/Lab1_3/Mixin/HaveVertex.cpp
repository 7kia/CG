#include "stdafx.h"
#include "HaveVertex.h"

CHaveThreeVertex::CHaveThreeVertex()
	: IHaveVertex()
	, m_vertex(3)
{
}

void CHaveThreeVertex::SetVertex(uint index, const SVertexP3NT2 & value)
{
	CheckIndex(index);
	m_vertex[index] = value;
}


SVertexP3NT2 CHaveThreeVertex::GetVertex(uint index) const
{
	CheckIndex(index);
	return m_vertex[index];
}

SVertexP3NT2 * CHaveThreeVertex::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return &m_vertex[index];
}


std::vector<SVertexP3NT2> CHaveThreeVertex::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for (size_t index = 0; index < 3; ++index)
	{
		result[index] = m_vertex[index];
	}
	return result;
}

void CHaveThreeVertex::SetPosition(uint index, const glm::vec3 & position)
{
	CheckIndex(index);

	m_vertex[index].position = position;
}

glm::vec3 CHaveThreeVertex::GetPosition(uint index) const
{
	CheckIndex(index);

	return m_vertex[index].position;
}

void CHaveThreeVertex::SetNoraml(uint index, const glm::vec3 & normal)
{
	CheckIndex(index);

	m_vertex[index].normal = normal;
}

glm::vec3 CHaveThreeVertex::GetNoraml(uint index) const
{
	CheckIndex(index);

	return m_vertex[index].normal;
}

void CHaveThreeVertex::SetTexCoordinate(uint index, const glm::vec2 & texCoordinate)
{
	CheckIndex(index);

	m_vertex[index].texCoord = texCoordinate;
}

glm::vec2 CHaveThreeVertex::GetTexCoordinate(uint index) const
{
	CheckIndex(index);

	return m_vertex[index].texCoord;
}


void CHaveThreeVertex::CheckIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_vertex.size())))
	{
		throw std::runtime_error("SVertexP3NT2 have the index not exist");
	}
}

CHaveReferenceVertex::CHaveReferenceVertex(size_t amountVertex)
	: IHaveVertex()
	, m_pVertex(amountVertex)

{
}

void CHaveReferenceVertex::SetVertex(uint index, const SVertexP3NT2 & value)
{
	CheckIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
 
}


SVertexP3NT2 CHaveReferenceVertex::GetVertex(uint index) const
{
	CheckIndex(index);
	return *m_pVertex[index][0];
}

SVertexP3NT2 * CHaveReferenceVertex::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return m_pVertex[index][0];
}


std::vector<SVertexP3NT2> CHaveReferenceVertex::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
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
		throw std::runtime_error("SVertexP3NT2 have the index not exist");
	}
}

void CHaveReferenceVertex::AddReferenceVertex(uint index, SVertexP3NT2 * value)
{
	CheckIndex(index);

	m_pVertex[index].push_back(value);
}
