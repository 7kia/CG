#include "stdafx.h"
#include "HaveVertex.h"


SVertexP3NT2::SVertexP3NT2(const glm::vec3 & position
	, const glm::vec2 & texCoord
	, const glm::vec3 & normal)
	: position(position)
	, texCoord(texCoord)
	, normal(normal)
{
}

CHaveVertexes::CHaveVertexes()
	: IHaveVertex()
	, m_vertices(3)
{
}

CHaveVertexes::CHaveVertexes(uint size)
	: IHaveVertex()
{
	if (size < 3)
	{
		throw std::logic_error("Shape must have more 2 vertex");
	}
	m_vertices.resize(size);
}

void CHaveVertexes::SetVertex(uint index, const SVertexP3NT2 & value)
{
	CheckIndex(index);
	m_vertices[index] = value;
}


SVertexP3NT2 CHaveVertexes::GetVertex(uint index) const
{
	CheckIndex(index);
	return m_vertices[index];
}

SVertexP3NT2 * CHaveVertexes::GetReferenceToVertex(int index)
{
	CheckIndex(index);
	return &m_vertices[index];
}


std::vector<SVertexP3NT2> CHaveVertexes::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for (size_t index = 0; index < 3; ++index)
	{
		result[index] = m_vertices[index];
	}
	return result;
}

void CHaveVertexes::SetPosition(uint index, const glm::vec3 & position)
{
	CheckIndex(index);

	m_vertices[index].position = position;
}

glm::vec3 CHaveVertexes::GetPosition(uint index) const
{
	CheckIndex(index);

	return m_vertices[index].position;
}

void CHaveVertexes::SetNoraml(uint index, const glm::vec3 & normal)
{
	CheckIndex(index);

	m_vertices[index].normal = normal;
}

glm::vec3 CHaveVertexes::GetNoraml(uint index) const
{
	CheckIndex(index);

	return m_vertices[index].normal;
}

void CHaveVertexes::SetTexCoordinate(uint index, const glm::vec2 & texCoordinate)
{
	CheckIndex(index);

	m_vertices[index].texCoord = texCoordinate;
}

glm::vec2 CHaveVertexes::GetTexCoordinate(uint index) const
{
	CheckIndex(index);

	return m_vertices[index].texCoord;
}


void CHaveVertexes::CheckIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_vertices.size())))
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
