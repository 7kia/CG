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
	CheckVertexIndex(index);
	m_vertices[index] = value;
}


SVertexP3NT2 CHaveVertexes::GetVertex(uint index) const
{
	CheckVertexIndex(index);
	return m_vertices[index];
}

SVertexP3NT2 * CHaveVertexes::GetReferenceToVertex(int index)
{
	CheckVertexIndex(index);
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
	CheckVertexIndex(index);

	m_vertices[index].position = position;
}

glm::vec3 CHaveVertexes::GetPosition(uint index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].position;
}

void CHaveVertexes::SetNoraml(uint index, const glm::vec3 & normal)
{
	CheckVertexIndex(index);

	m_vertices[index].normal = normal;
}

glm::vec3 CHaveVertexes::GetNoraml(uint index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].normal;
}

void CHaveVertexes::SetTexCoordinate(uint index, const glm::vec2 & texCoordinate)
{
	CheckVertexIndex(index);

	m_vertices[index].texCoord = texCoordinate;
}

glm::vec2 CHaveVertexes::GetTexCoordinate(uint index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].texCoord;
}


void CHaveVertexes::CheckVertexIndex(uint index) const
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
	CheckVertexIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
 
}


SVertexP3NT2 CHaveReferenceVertex::GetVertex(uint index) const
{
	CheckVertexIndex(index);
	return *m_pVertex[index][0];
}

SVertexP3NT2 * CHaveReferenceVertex::GetReferenceToVertex(int index)
{
	CheckVertexIndex(index);
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

void CHaveReferenceVertex::SetPosition(uint index, const glm::vec3 & position)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->position = position;
	}
}

glm::vec3 CHaveReferenceVertex::GetPosition(uint index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->position;
}

void CHaveReferenceVertex::SetNoraml(uint index, const glm::vec3 & normal)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->normal = normal;
	}
}

glm::vec3 CHaveReferenceVertex::GetNoraml(uint index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->normal;
}

void CHaveReferenceVertex::SetTexCoordinate(uint index, const glm::vec2 & texCoordinate)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->texCoord = texCoordinate;
	}
}

glm::vec2 CHaveReferenceVertex::GetTexCoordinate(uint index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->texCoord;
}


void CHaveReferenceVertex::CheckVertexIndex(uint index) const
{
	if (!IsBetween(index, 0u, uint(m_pVertex.size())))
	{
		throw std::runtime_error("SVertexP3NT2 have the index not exist");
	}
}

void CHaveReferenceVertex::AddReferenceVertex(uint index, SVertexP3NT2 * value)
{
	CheckVertexIndex(index);

	m_pVertex[index].push_back(value);
}
