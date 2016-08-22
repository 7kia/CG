#include "stdafx.h"
#include "WeldVertexes.h"

IdentityShapeSharedPtr Weld(const IdentityShapeSharedPtr first
	, const IdentityShapeSharedPtr second
	, std::vector<std::pair<size_t, size_t>> indexesVertex
)
{
	IdentityShapeSharedPtr result = std::make_shared<CIdentity3DShape>();
	size_t amountVertexInFirst = first->GetAmountVertexes();

	if (amountVertexInFirst > 0)
	{
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


		std::vector<std::pair<size_t, uint32_t>> replaceIndexes;

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


		auto GetNewIndex = [amountIndexesInFirst](uint32_t oldIndex)
		{
			return uint32_t(oldIndex + amountIndexesInFirst);
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
			result->SetIndex(index, result->GetIndex(index) - uint32_t(replaceIndexes.size()) + 1);
		}

		for (const auto & element : replaceIndexes)
		{
			result->SetIndex(element.first, element.second);
		}

	}

	return result;
}

bool WeldToFirst(CIdentity3DShape* first
	, const CIdentity3DShape* second
	, std::vector<std::pair<size_t, size_t>> indexesVertex)
{
	size_t amountVertexInFirst = first->GetAmountVertexes();

	if ((amountVertexInFirst > 0) && (indexesVertex.size() > 0))
	{
		size_t amountVertexInSecond = second->GetAmountVertexes();
		size_t amountIndexesInFirst = first->GetAmountVIndexes();
		size_t amountIndexesInSecond = second->GetAmountVIndexes();

		// Find max index
		auto indexes = first->GetIndexes();
		size_t maxIndex = *std::max_element(indexes.begin(), indexes.end());

		// allocate memory
		first->ResizeVertexArray(amountVertexInFirst + amountVertexInSecond - indexesVertex.size());
		first->ResizeIndexArray(amountIndexesInFirst + amountIndexesInSecond);

		// Do copy vertexes and indexes from second shape
		auto vertexesFromSecond = second->GetVertexes();
		auto indexesFromSecond = second->GetIndexes();


		std::vector<std::pair<size_t, uint32_t>> replaceIndexes;

		// delete weld vertex from copy second shape
		auto sortedIndexesVertex = indexesVertex;

		auto comparePair = [](std::pair<size_t, size_t> first, std::pair<size_t, size_t> second)
		{
			return first.second < second.second;
		};
		std::sort(sortedIndexesVertex.begin(), sortedIndexesVertex.end(), comparePair);
		std::reverse(sortedIndexesVertex.begin(), sortedIndexesVertex.end());
		for (const auto & pair : sortedIndexesVertex)
		{

			vertexesFromSecond.erase(vertexesFromSecond.begin() + pair.second);
			//++indexPreviousDelete;
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

		// compute new value for indexes from copy second shape
		auto GetNewIndex = [maxIndex](uint32_t oldIndex)
		{
			return oldIndex + uint32_t(maxIndex) + 1;
		};
		boost::transform(indexesFromSecond, indexesFromSecond.begin(), GetNewIndex);

		///////////////////
		// Record from copy second shape in first
		for (size_t index = amountVertexInFirst; index <= (first->GetAmountVertexes() - indexesVertex.size()); ++index)// TODO :!!!
		{
			first->SetVertex(index, vertexesFromSecond[index - amountVertexInFirst]);
		}
		for (size_t index = amountIndexesInFirst; index < first->GetAmountVIndexes(); ++index)
		{
			first->SetIndex(index, indexesFromSecond[index - amountIndexesInFirst]);
		}


		// Search replace vertexes
		for (const auto & pair : indexesVertex)
		{
			// Замена индекса
			for (size_t index = amountIndexesInFirst; index < first->GetAmountVIndexes(); ++index)
			{
				if (first->GetIndex(index) == (pair.second + maxIndex + 1))
				{
					//result->SetIndex(index, firstIndex);
					replaceIndexes.push_back({ index, pair.first });
				}
			}
		}

		// Compute new value for indexes from second shape
		// with accounting delete vertexes
		for (size_t index = amountIndexesInFirst; index < first->GetAmountVIndexes(); ++index)
		{
			first->SetIndex(index, first->GetIndex(index) - uint32_t(replaceIndexes.size()) + 1);
		}

		// Replace
		for (const auto & element : replaceIndexes)
		{
			first->SetIndex(element.first, element.second);
		}

		return true;
	}

	return false;
}

VectorPairsIndexes FindCommonVertexes(const IdentityShapeSharedPtr first, const IdentityShapeSharedPtr second)
{
	VectorPairsIndexes result;
	size_t amountVertexInFirst = first->GetAmountVertexes();
	size_t amountVertexInSecond = second->GetAmountVertexes();


	for (size_t firstIndex = 0; firstIndex < amountVertexInFirst; ++firstIndex)
	{
		auto firstVertex = first->GetVertexPosition(firstIndex);
		for (size_t secondIndex = 0; secondIndex < amountVertexInSecond; ++secondIndex)
		{
			if (firstVertex == second->GetVertexPosition(secondIndex))
			{
				result.push_back({ firstIndex , secondIndex });
			}
		}
	}

	return result;
}

VectorPairsIndexes FindCommonVertexes(const std::vector<SVertexP3NT2>& first, const std::vector<SVertexP3NT2>& second)
{
	VectorPairsIndexes result;

	for (size_t firstIndex = 0; firstIndex < first.size(); ++firstIndex)
	{
		const auto & firstVertex = first[firstIndex];
		for (size_t secondIndex = 0; secondIndex < second.size(); ++secondIndex)
		{
			if (firstVertex.position == second[secondIndex].position)
			{
				result.push_back({ firstIndex , secondIndex });
			}
		}
	}

	return result;
}
