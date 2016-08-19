#include "stdafx.h"
#include "3DShape.h"

I3DShape::I3DShape()
	: IDrawable()
{
}

CIdentity3DShape::CIdentity3DShape()
	: C3DShape()
	, CHaveVertexes()

{
}

void CIdentity3DShape::Draw() const
{
	glPushMatrix();
	glMultMatrixf(glm::value_ptr(m_transform));

	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});

	glPopMatrix();
}

std::vector<SVertexP3NT2> CIdentity3DShape::GetVertexes() const
{
	std::vector<SVertexP3NT2> result;
	for //(const auto & index : m_indicies)
		(size_t index = 0; index < m_vertices.size(); ++index)
	{
		auto vertexWithTransform = m_vertices[index];
		vertexWithTransform.position = GetVertexPosition(index);
		result.push_back(vertexWithTransform);
	}
	return result;
}

glm::vec3 CIdentity3DShape::GetVertexPosition(uint index) const
{
	CheckVertexIndex(index);

	auto currentPosition = glm::translate(GetTransform(), m_vertices[index].position);
	return glm::vec3(currentPosition[3][0], currentPosition[3][1], currentPosition[3][2]);
}



C3DShape::C3DShape()
	: I3DShape()
	, CTransformable()
{
}

IdentityShapeSharedPtr Weld(const IdentityShapeSharedPtr first
							, const IdentityShapeSharedPtr second
							, std::vector<std::pair<size_t, size_t>> indexesVertex
							)
{
	IdentityShapeSharedPtr result = std::make_shared<CIdentity3DShape>();
	size_t amountVertexInFirst = first->GetAmountVertexes();
	size_t amountVertexInSecond = second->GetAmountVertexes();
	size_t amountIndexesInFirst = first->GetAmountVIndexes();
	size_t amountIndexesInSecond = second->GetAmountVIndexes();

	result->ResizeVertexArray(amountVertexInFirst + amountVertexInSecond - indexesVertex.size());
	result->ResizeIndexArray(amountIndexesInFirst + amountIndexesInSecond);
	
	// Записываем первую фигуру
	for (size_t index = 0; index < amountVertexInFirst; ++index)
	{
		result->SetVertex(index, first->GetVertex(index));
	}
	for (size_t index = 0; index < amountIndexesInFirst; ++index)
	{
		result->SetIndex(index, first->GetIndex(index));
	}

	// Чтобы индексы копируемых фигур не совпадали
	auto indexes = result->GetIndexes();
	size_t maxIndex = *std::max_element(indexes.begin(), indexes.end());
	
	// Удалаем вершину и её индекс
	auto vertexesFromSecond = second->GetVertexes();
	auto indexesFromSecond = second->GetIndexes();


	std::vector<std::pair<size_t, size_t>> replaceIndexes;

	// удаление соединяемой вершины(из второй фигуры)
	size_t indexPreviousDelete = 0;
	auto sortedIndexesVertex = indexesVertex;
	std::sort(sortedIndexesVertex.begin(), sortedIndexesVertex.end());
	std::reverse(sortedIndexesVertex.begin(), sortedIndexesVertex.end());
	for (const auto & pair : sortedIndexesVertex)
	{
		vertexesFromSecond.erase(vertexesFromSecond.begin() + pair.second - indexPreviousDelete);
		++indexPreviousDelete;
	}
	// Замена второго на первый
	/*
		std::replace_if(indexesFromSecond.begin()
					, indexesFromSecond.end()
					, [&](uint32_t index)
						{
							return index == secondIndex;
						}
					, firstIndex);
	*/


	auto GetNewIndex = [amountIndexesInFirst](size_t oldIndex)
	{
		return oldIndex + amountIndexesInFirst;
	};
	boost::transform(indexesFromSecond, indexesFromSecond.begin(), GetNewIndex);

	///////////////////
	// Запись из второй фигуры
	for (size_t index = amountVertexInFirst; index <= (result->GetAmountVertexes() - indexesVertex.size() + 1); ++index)
	{
		result->SetVertex(index, vertexesFromSecond[index - amountVertexInFirst]);
	}
	for (size_t index = amountIndexesInFirst; index < result->GetAmountVIndexes(); ++index)
	{
		result->SetIndex(index, indexesFromSecond[index - amountIndexesInFirst]);
	}

	// Search replace vertex
	for (const auto & pair : indexesVertex)
	{
		// Замена индекса
		for (size_t index = amountIndexesInFirst; index < result->GetAmountVIndexes(); ++index)
		{
			if (result->GetIndex(index) == (pair.second + maxIndex + 1))
			{
				//result->SetIndex(index, firstIndex);
				replaceIndexes.push_back({ index, pair.first });
			}
		}
	}
	
	for (size_t index = amountIndexesInFirst; index < result->GetAmountVIndexes(); ++index)
	{
		result->SetIndex(index, result->GetIndex(index) - replaceIndexes.size() + 1);
	}

	for (const auto & element : replaceIndexes)
	{
		result->SetIndex(element.first, element.second);
	}

	return result;
}
