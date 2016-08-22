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
{
}

CHaveVertexes::CHaveVertexes(size_t size)
	: IHaveVertex()
{
	if (size < 3)
	{
		throw std::logic_error("Shape must have more 2 vertex");
	}
	m_vertices.resize(size);
}

void CHaveVertexes::ResizeVertexArray(size_t newSize)
{
	m_vertices.resize(newSize, SVertexP3NT2());
}

size_t CHaveVertexes::GetAmountVertexes() const
{
	return m_vertices.size();
}

void CHaveVertexes::ResizeIndexArray(size_t newSize)
{
	m_indicies.resize(newSize, 0u);
}

size_t CHaveVertexes::GetAmountVIndexes() const
{
	return m_indicies.size();
}

void CHaveVertexes::SetVertex(size_t index, const SVertexP3NT2 & value)
{
	CheckVertexIndex(index);
	m_vertices[index] = value;
}


SVertexP3NT2 CHaveVertexes::GetVertex(size_t index) const
{
	CheckVertexIndex(index);
	return m_vertices[index];
}

SVertexP3NT2 * CHaveVertexes::GetReferenceToVertex(int index)
{
	CheckVertexIndex(index);
	return &m_vertices[index];
}


std::vector<SVertexP3NT2> CHaveVertexes::GetSourceVertexes() const
{
	return m_vertices;
}

std::vector<uint32_t> CHaveVertexes::GetIndexes() const
{
	return m_indicies;
}

void CHaveVertexes::SetSourceVertexPosition(size_t index, const glm::vec3 & position)
{
	CheckVertexIndex(index);

	m_vertices[index].position = position;
}

glm::vec3 CHaveVertexes::GetSourceVertexPosition(size_t index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].position;
}

void CHaveVertexes::SetVertexNormal(size_t index, const glm::vec3 & normal)
{
	CheckVertexIndex(index);

	m_vertices[index].normal = normal;
}

glm::vec3 CHaveVertexes::GetVertexNormal(size_t index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].normal;
}

void CHaveVertexes::SetVertexTexCoordinate(size_t index, const glm::vec2 & texCoordinate)
{
	CheckVertexIndex(index);

	m_vertices[index].texCoord = texCoordinate;
}

glm::vec2 CHaveVertexes::GetVertexTexCoordinate(size_t index) const
{
	CheckVertexIndex(index);

	return m_vertices[index].texCoord;
}

void CHaveVertexes::SetIndex(size_t index, size_t newIndex)
{
	CheckIdIndex(index);

	m_indicies[index] = newIndex;
}

size_t CHaveVertexes::GetIndex(size_t index) const
{
	CheckIdIndex(index);

	return m_indicies[index];

}


void CHaveVertexes::CheckVertexIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, size_t(m_vertices.size())))
	{
		throw std::runtime_error("SVertexP3NT2 have the index not exist");
	}
}

void CHaveVertexes::CheckIdIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, size_t(m_indicies.size())))
	{
		throw std::runtime_error("SVertexP3NT2 have index with the id");
	}
}

CHaveReferenceVertex::CHaveReferenceVertex(size_t amountVertex)
	: IHaveVertex()
	, m_pVertex(amountVertex)

{
}

void CHaveReferenceVertex::SetVertex(size_t index, const SVertexP3NT2 & value)
{
	CheckVertexIndex(index);

	for (auto & element : m_pVertex[index])
	{
		*element = value;
	}
 
}


SVertexP3NT2 CHaveReferenceVertex::GetVertex(size_t index) const
{
	CheckVertexIndex(index);
	return *m_pVertex[index][0];
}

SVertexP3NT2 * CHaveReferenceVertex::GetReferenceToVertex(int index)
{
	CheckVertexIndex(index);
	return m_pVertex[index][0];
}


std::vector<SVertexP3NT2> CHaveReferenceVertex::GetSourceVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for (size_t index = 0; index < m_pVertex.size(); ++index)
	{
		result.push_back(*m_pVertex[index][0]);
	}
	return result;
}

void CHaveReferenceVertex::SetSourceVertexPosition(size_t index, const glm::vec3 & position)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->position = position;
	}
}

glm::vec3 CHaveReferenceVertex::GetSourceVertexPosition(size_t index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->position;
}

void CHaveReferenceVertex::SetVertexNormal(size_t index, const glm::vec3 & normal)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->normal = normal;
	}
}

glm::vec3 CHaveReferenceVertex::GetVertexNormal(size_t index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->normal;
}

void CHaveReferenceVertex::SetVertexTexCoordinate(size_t index, const glm::vec2 & texCoordinate)
{
	CheckVertexIndex(index);
	for (auto & element : m_pVertex[index])
	{
		element->texCoord = texCoordinate;
	}
}

glm::vec2 CHaveReferenceVertex::GetVertexTexCoordinate(size_t index) const
{
	CheckVertexIndex(index);

	return m_pVertex[index][0]->texCoord;
}


void CHaveReferenceVertex::CheckVertexIndex(size_t index) const
{
	if (!IsBetween(index, 0llu, m_pVertex.size()))
	{
		throw std::runtime_error("SVertexP3NT2 have the index not exist");
	}
}

void CHaveReferenceVertex::AddReferenceVertex(size_t index, SVertexP3NT2 * value)
{
	CheckVertexIndex(index);

	m_pVertex[index].push_back(value);
}
